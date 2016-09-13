----------------------------------------------------------------------------------------------------
--  IFComicDownload��lua�ű����ز��Թ��� ver 1.0
--  2016-9-5 13:19:37 by seedjyh@gmail.com
----------------------------------------------------------------------------------------------------
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

-- ����һ��lua�ļ�·���б�������г�Ա
function LoadLuaFileList(lua_file_list)
    for _,v in pairs(lua_file_list) do
        print('loading: ' .. v)
        dofile(v)
    end
end

-- �ַ������
function lua_string_split(str, split_char)
    local sub_str_tab = {};
    local i = 0;
    local j = 0;
    while true do
        j = string.find(str, split_char,i+1); -- ��Ŀ�괮str��i+1���ַ���ʼ����ָ����
        if j == nil then
            table.insert(sub_str_tab,str);
            break;
        end;
        table.insert(sub_str_tab,string.sub(str,i+1,j-1));
        i = j;
    end
    return sub_str_tab;
end

-- ��ȡһ��Ŀ¼�µ�����lua�ļ���·���б�
function GetAllLuaFilesInPath(path)
    if string.sub(path, string.len(path)) ~= '\\' then
        path = path .. '\\'
    end
    local handle = io.popen("ls " .. path)
    local l = handle:read("*all")
    handle:close()
    local s = lua_string_split(l, '\n')
    
    local result_list = {}
    for _,v in pairs(s) do
        _, end_index = string.find(v, '.lua')
        if end_index == string.len(v) then
            table.insert(result_list, path .. v)
        end
    end
    return result_list
end
