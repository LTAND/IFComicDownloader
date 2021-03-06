------------------------------------------------------------
---http://www.2manhua.com
------------------------------------------------------------
function Analyse(url)
    local page_type = GetPageType(url)
    if type(page_type) ~= "string" then
        return nil, "GetPageType failed for url:" .. url
    end
    -- guess the type of page
    if "comic" == page_type then
        return ComicUrlAnalyse(url, pagestr, "")
    end
    if "volume" == page_type then
        return VolumeUrlAnalyse(url, pagestr, "")
    end
    if "picture" == page_type then
        return PictureUrlAnalyse(url, pagestr, "")
    end
    return nil, "Unknown page type:" .. page_type .. " for url:" .. url
end
------------------------------------------------------------
site_mode = ".2manhua.com" -- .XXX.com
site_chinese_name = "������" --XXXXX
site_thread_count = 100 -- 1~100
site_resource_CD  = 0 -- second
site_host = "http://www.2manhua.com/" --http://www.XXX.com/
------------------------------------------------------------
function GetPageType(url)
    -- comic   page URL sample: http://www.2manhua.com/comic/29609/
    -- volume  page URL sample: http://www.2manhua.com/comic/29609/01.html
    -- picture page URL sample: http://www.2manhua.com/comic/29609/01.html?p=1
    if string.find(url, '?') then return "picture" end
    if string.find(url, '.html') then return "volume" end
    return "comic"
end
