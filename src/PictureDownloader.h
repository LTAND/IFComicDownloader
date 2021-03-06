//
//   File name      : PictureDownloader.h
//
//   Code by        : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2016-01-03 07:21:41
//

#ifndef _PICTUREDOWNLOADER_H_
#define _PICTUREDOWNLOADER_H_ 1

// Tested or implemented header
// ...

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
#include "IFLuaHandler/LuaState.h"
#include "IFDataType/DataHolder.h"

// Headers of current project
// ...

class PictureDownloader
{
    LUA_STATE_PTR lua_state_;
    std::string comic_title_;
    std::string volume_title_;
public:
    PictureDownloader(LUA_STATE_PTR lua_state)
    :   lua_state_(lua_state){}

    void set_comic_title(const std::string &kTitle) { comic_title_ = kTitle; return; }
    void set_volume_title(const std::string &kTitle) { volume_title_ = kTitle; return; }

    void Download(const std::string &kURL, const Tstring &kDownloadRootPath);

protected:
private:
    static void WriteFile(const Tstring &kPath, DATAHOLDER_PTR data);
    static std::string GetFileNameExtentionFromFileURL(const std::string &kURL);
    static Tstring GenerateLocalFilePath_FullImageFileName(
        const Tstring &kDownloadPath,
        const std::string &kComicTitle,
        const std::string &kVolumeTitle,
        int picture_index,
        const Tstring &kExtensionName // 扩展名前面有点（.）
    );
    static Tstring GenerateLocalFilePath_NoComicTitleInImageFileName(
        const Tstring &kDownloadPath,
        const std::string &kComicTitle,
        const std::string &kVolumeTitle,
        int picture_index,
        const Tstring &kExtensionName // 扩展名前面有点（.）
    );
    // 检查图片文件数据的有效性。有效返回true。
    bool CheckImageFileValidity(const DATAHOLDER_PTR &kData);
};

#endif
