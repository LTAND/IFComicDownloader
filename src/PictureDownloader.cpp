//
//   File name      : PictureDownloader.cpp
//
//   Code by        : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2016-01-03 07:27:32
//

// Tested or implemented header
#include "PictureDownloader.h"

// C system headers
// ...

// C++ system headers
#include <iostream>

// Headers from other projects
#include "IFOperator/NumberOperator.h"
#include "IFDataType/Tstring.h"
#include "IFOperator/CodeTransformer.h"
#include "IFCurlAdaptor/UrlDownloaderFactory.h"
#include "IFMacros/BasicOperateMacro.h"
#include "IFOperator/PathHandler.h"

// Headers of current project
#include "exception/UrlAnalyseFailedException.h"
#include "exception/DownloadFailedException.h"
#include "exception/CallLuaFunctionFailed.h"
#include "exception/InvalidImageFileException.h"
#include "ProgramArguments.h"
#include "CacheManager.h"
#include "log/include/log.h"
#include "log/include/log_handle.h"

void PictureDownloader::Download(const std::string &kURL, const Tstring &kDownloadRootPath)
{
    LOG_HANDLE log_handle;
    log_handle_init(&log_handle);
    log_info(&log_handle, "Start downloading a picture, URL=%s", kURL.c_str());
    while (1)
    {
        // getting file URL
        const char *kResult = NULL;
        const char *kErrorMessage = NULL;
        if (!lua_state_->CallFunction("PictureUrlAnalyse", "s>s", kURL.c_str(), &kResult, &kErrorMessage))
        {
             throw UrlAnalyseFailedException(kURL, std::string((kErrorMessage != NULL) ? kErrorMessage : ""));
        }
        const std::string kAnalyseResult(kResult);

        if (!lua_state_->CallFunction("FindFileUrl", "s>s", kAnalyseResult.c_str(), &kResult, &kErrorMessage))
        {
            throw UrlAnalyseFailedException(kURL, std::string((kErrorMessage != NULL) ? kErrorMessage : ""));
        }
        const std::string kFileURL(kResult);

        // getting file index (from 1)
        int file_index = 0;
        if (!lua_state_->CallFunction("GetPageIndexFromURL", "s>i", kURL.c_str(), &file_index, &kErrorMessage))
        {
            throw UrlAnalyseFailedException(kURL, std::string((kErrorMessage != NULL) ? kErrorMessage : ""));
        }

        //////////////////////////////////////////////////////////////////////////
        // generate file path
        Tstring file_path = GenerateLocalFilePath_FullImageFileName(
            kDownloadRootPath,
            comic_title_,
            volume_title_,
            file_index,
            CodeTransformer::TransStringToTString(GetFileNameExtentionFromFileURL(kFileURL))
        );
        if (PathHandler::isTooLongToWrite(file_path))
        {
            file_path = GenerateLocalFilePath_NoComicTitleInImageFileName(
                kDownloadRootPath,
                comic_title_,
                volume_title_,
                file_index,
                CodeTransformer::TransStringToTString(GetFileNameExtentionFromFileURL(kFileURL))
                );
        }
        if (PathHandler::isTooLongToWrite(file_path))
        {
            printf("ERROR! Image path is too long to write.\n");
            return;
        }
        //////////////////////////////////////////////////////////////////////////

        if (PathHandler::CheckFileExistance(file_path))
        {
            return;
        }
        // download file
        UrlDownloaderFactory downloader_factory(ProgramArguments::Instance().curl_dll_path());
        URLDOWNLOADER_PTR downloader = downloader_factory.Create();
        try
        {
            DATAHOLDER_PTR data = downloader->Download(kFileURL, kURL, std::string(""));
            if (!CheckImageFileValidity(data))
            {
                throw InvalidImageFileException(kFileURL, kURL);
            }
            WriteFile(file_path.c_str(), data);
            break;
        }
        catch (DownloadFailedException &e)
        {
            printf("%s\n", e.message().c_str());
            printf("Download failed, retry... ");
            // 这里本来应该根据具体站点的脚本函数needRefleshPicturePage返回值来决定：是否要清除PicturePage的内容（和cache），并重新下载PicturePage。
            // 不过这里暂且直接清除cache并重新下载PicturePage。
            CacheManager::Instance().remove(kURL);
        }
        catch (InvalidImageFileException &e)
        {
            printf("%s\n", e.message().c_str());
            printf("Invalid image file, retry... ");
            // 这里本来应该根据具体站点的脚本函数needRefleshPicturePage返回值来决定：是否要清除PicturePage的内容（和cache），并重新下载PicturePage。
            // 不过这里暂且直接清除cache并重新下载PicturePage。
            CacheManager::Instance().remove(kURL);
        }
    }
    
    return;
}

void PictureDownloader::WriteFile(const Tstring &kPath, DATAHOLDER_PTR data)
{
    FILE *fp = _tfopen(kPath.c_str(), _T("wb"));
    if (fwrite(data->content(), 1, data->size(), fp) != data->size())
    {
        throw 1;
    }
    MY_FCLOSE(fp);
    return;
}

std::string PictureDownloader::GetFileNameExtentionFromFileURL(const std::string &kURL)
{
    std::string result(strrchr(kURL.c_str(), '.'));

    // 有些URL后面还带上一个类似动态页面的参数，例如：http://manhua1025.61-174-50-141.cdndm5.com/20/19620/245859/1_9128.jpg?cid=245859&key=eca7f3ed56d8b4c2872ab88c33bddd81
    // 所以要去掉问号后面的部分。
    const char *kQuestionMark = strchr(result.c_str(), '?');
    if (kQuestionMark != NULL)
    {
        result.resize(kQuestionMark - result.c_str());
    }
    return result;
}

Tstring PictureDownloader::GenerateLocalFilePath_FullImageFileName(
    const Tstring &kDownloadPath,
    const std::string &kComicTitle,
    const std::string &kVolumeTitle,
    int picture_index,
    const Tstring &kExtensionName // 扩展名前面有点（.）
    )
{
    const Tstring kFilePath =
        kDownloadPath +
        PathHandler::ValidateName(CodeTransformer::TransStringToTString(kComicTitle + "_" + kVolumeTitle + "_")) +
        NumberOperator::ItoA(picture_index, Tstring(_T("%06u"))) +
        kExtensionName;
    return kFilePath;
}

Tstring PictureDownloader::GenerateLocalFilePath_NoComicTitleInImageFileName(
    const Tstring &kDownloadPath,
    const std::string &kComicTitle,
    const std::string &kVolumeTitle,
    int picture_index,
    const Tstring &kExtensionName // 扩展名前面有点（.）
    )
{
    const Tstring kFilePath =
        kDownloadPath +
        PathHandler::ValidateName(CodeTransformer::TransStringToTString(kVolumeTitle + "_")) +
        NumberOperator::ItoA(picture_index, Tstring(_T("%06u"))) +
        kExtensionName;
    return kFilePath;
}

bool PictureDownloader::CheckImageFileValidity(const DATAHOLDER_PTR &kData)
{
    bool lua_result = false;
    const char *kErrorMessage = NULL;
    std::string local_data(kData->content(), kData->size());
    if (!lua_state_->CallFunction("CheckImageFileValidity", "S>b", &local_data, &lua_result, &kErrorMessage))
    {
        throw CallLuaFunctionFailed("CheckImageFileValidity", std::string((kErrorMessage != NULL) ? kErrorMessage : ""));
    }
    return lua_result;
}
