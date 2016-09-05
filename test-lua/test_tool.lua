----------------------------------------------------------------------------------------------------
--  IFComicDownload��lua�ű����ز��Թ��� ver 1.0
--  2016-9-5 13:19:37 by seedjyh@gmail.com
----------------------------------------------------------------------------------------------------
-- ����ļ��ǲ���lua�ű��Ĺ��ߺ������ϡ�
-- ����4����
-- 1. ����script/api/lua�ű����Լ�script/sites/www.XXX.com/*.lua�������ĸ�վ����Ҫָ�����ű���
-- 2. ��ȡһ��ָ����html�ļ�����������������ص����أ���
-- 3. ������Ҫ���Եĺ�������ֹһ����������Analyse��Get�����������
-- 4. ��ӡ���н����
----------------------------------------------------------------------------------------------------
-- step 1
function GetApiScriptList()
    local list = {}
    list[1 + #list] = 'lib.lua'
    list[1 + #list] = 'eval.lua'
    list[1 + #list] = 'site_read.lua'
    return list
end

function GetSiteScriptList()
    local list = {}
    list[1 + #list] = 'comic.page.analyse.lua'
    list[1 + #list] = 'volume.page.analyse.lua'
    list[1 + #list] = 'picture.page.analyse.lua'
    list[1 + #list] = 'url.analyse.lua'
    return list
end

function GetSiteScriptList_extra()
    local list = {}
    return list
end

function AppendPrefixToList(prefix, list)
    local result = {}
    for _,v in pairs(list) do
        result[1 + #result] = prefix .. v
    end
    return result
end

function ConnectTwoList(list_a, list_b)
    local result = {}
    for _,v in pairs(list_a) do
        result[1 + #result] = v
    end
    for _,v in pairs(list_b) do
        result[1 + #result] = v
    end
    return result
end

-- ��ȡ������ĳ����վ��ҳ����Ҫ���ص�lua�ļ����б�
-- ����������������վ��Ӧ�����ű����ļ��е����֣�����"www.ikanman.com"
-- ���أ�һ��table��key������������1��ʼ��š�
-- ʹ��������
-- for _,v in pairs(GetRequiredLuaScriptList('www.ikanman.com')) do
--     print(v)
-- end
function GetRequiredLuaScriptList(site_dir_name)
    local script_root_path = 'M:\\GitHubRepositories\\IFComicDownloader\\script\\'
    local result = {}
    
    result = ConnectTwoList(result, AppendPrefixToList("api\\", GetApiScriptList()))
    result = ConnectTwoList(result, AppendPrefixToList("sites\\" .. site_dir_name .. "\\", ConnectTwoList(GetSiteScriptList(), GetSiteScriptList_extra())))
    return AppendPrefixToList(script_root_path, result)
end

-- ��ȡһ���ļ����ļ�·���Ӳ���file_path���룩�������ļ����ݡ�
-- ����ֵ��
-- ����ɹ��������ļ����ݣ�string��ʽ��
-- ���������һ������ֵ��nil���ڶ�������ֵ�Ǵ�����Ϣ��string��ʽ��
function ReadFile(file_path)
    local file, errmsg = io.open(file_path, "rb")
    if not file then return nil, errmsg end
    local data = file:read("*all")
    file:close()
    return data
end
