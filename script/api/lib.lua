function JumpStr(pagestr, start_index, str_to_jump, jump_count, str_to_ignore) -- ���������str_to_ignore��������ignore_str�ٽ�����һ������
    local search_start_index = start_index

    for i=1, jump_count do
        while true do -- ����Ҫ����һ������ignore_str��ÿ��while������һ��ignore_str
            local result_start_index, result_end_index = string.find(pagestr, str_to_jump, search_start_index, true)
            if type(result_end_index) ~= "number" then
                return nil
            end
            
            if type(str_to_ignore) == "string" then -- ����ignore�ַ�����������
                local ignore_start_index, ignore_end_index = string.find(pagestr, str_to_ignore, search_start_index, true)
                if type(ignore_start_index) ~= "number" or  -- û���ҵ�ignore�ַ���
                   ignore_start_index > result_start_index then -- ignore�ַ�����Ŀ���ַ���֮��
                    search_start_index = result_end_index + 1
                    break
                else
                    search_start_index = ignore_end_index + 1
                end
            else
                search_start_index = result_end_index + 1
                break
            end
        end
    end

    return search_start_index
end


function GetStr(pagestr, start_index, char_to_end)
    if type(pagestr) ~= "string" then
        return nil, "GetStr failed because pagestr is not a string. Its type is " .. type(pagestr)
    end
    if type(start_index) ~= "number" then
        return nil, "GetStr failed because start_index is not a number. Its type is " .. type(start_index)
    end
    
    local _, end_index = string.find(pagestr, "[" .. char_to_end .. "]", start_index)
    if type(end_index) ~= "number" then
        end_index = string.len(pagestr)
    else
        end_index = end_index - 1
    end
    return string.sub(pagestr, start_index, end_index)
end

function GetURLHost(url)
    if type(url) ~= "string" then
        return nil, "GeURLHost failed because url is not a string. Its type is " .. type(url)
    end
    prefix_length = string.len("http://")
    if string.len(url) > prefix_length then
        slash_index, _ = string.find(url, "/", prefix_length + 1, true)
        if type(slash_index) ~= "number" then
            return url
        end
        return string.sub(url, 1, slash_index - 1)
    end
end

--��ASCII�������ת���ַ�
function AscIICodeToChar(ascii_code)
    assert("number" == type(ascii_code) )
    return string.format("%c", ascii_code)
end

--���ַ�ת��ASCII�������
function CharToAscIICode(char)
    assert("string" == type(char) )
    return tonumber(string.byte(char, 1, 1))
end

--��ʮ�����Ƶ�ASCIIת���ַ�����"67"ת��"g"(0x67)
function HexAscIICodeToChar(hex_ascii)
    local hex_str    = "0x" .. hex_ascii
    local ascii_code = tonumber(hex_str)
    return AscIICodeToChar(ascii_code)
end

--�ҵ�������ĳ�Ӵ���λ��
function GetLastPos(str, substr)
    local result_begin = nil
    local result_end   = nil
    
    local start_index = 1
    while true do
        local temp_begin = nil
        local temp_end   = nil
        temp_begin, temp_end = string.find(str, substr, start_index, true)
        if "number" == type(temp_begin) and "number" == type(temp_end) then
            result_begin = temp_begin
            result_end   = temp_end
            start_index = result_end + 1
        else
            break
        end
    end
    return result_begin, result_end
end

--��str�г���������ender֮����ַ�ȥ��
function CutTailAfterLastKey(str, ender)
    local last_begin = nil
    local last_end   = nil
    local result     = str
    
    last_begin, last_end = GetLastPos(str, ender)
    if "number" == type(last_begin) and "number" == type(last_end) then
        result = string.sub(result, 1, last_end)
    end
    
    return result
end

--��װһ������URL��һ�����URL
function BindURL(absoluted_url, related_url)
    if type(absoluted_url) ~= "string" then
        return nil, "BindURL failed because absoluted_url is not a string. Its type is " .. type(absoluted_url)
    end
    if type(related_url) ~= "string" then
        return nil, "BindURL failed because related_url is not a string. Its type is " .. type(related_url)
    end
    local prefix = absoluted_url
    local suffix = related_url
    local keep_loop = true
    while keep_loop do
        local start_index  = nil
        local finish_index = nil
        
        keep_loop = false
        
        -- XXX + "./XXX"
        start_index, finish_index = string.find(suffix, "./", 1, true)
        if 1 == start_index then
            prefix = CutTailAfterLastKey(prefix, "/")
            suffix = string.sub(suffix, finish_index + 1, string.len(suffix) )
            keep_loop = true
        end
        
        -- XXX + "../XXX"
        start_index, finish_index = string.find(suffix, "../", 1, true)
        if 1 == start_index then
            prefix = CutTailAfterLastKey(prefix, "/")
            prefix = string.sub(prefix, 1, string.len(prefix) - string.len("/") )
            prefix = CutTailAfterLastKey(prefix, "/")
            suffix = string.sub(suffix, finish_index + 1, string.len(suffix) )
            keep_loop = true
        end    
    end
    
    return prefix .. suffix
end

--ȡ��һ��URL�ӿ�ͷ�����һ��'/'��ǰ׺URL��
function GetLongestHost(url)
    local _, end_index = GetLastPos(url, "/")
    return string.sub(url, 1, end_index)
end

-- ɾ��һ���ַ�����ͷ�ͽ�β�����в��ɼ��ַ���' ', '\t', '\r', '\n'��
function Strip(str)
    while true do
        begin_char = string.sub(str, 1, 1)
        if begin_char == ' ' or begin_char == '\t' or begin_char == '\r' or begin_char == '\n' then
            str = string.sub(str, 2)
        else
            break
        end
    end
    
    while true do
        end_char = string.sub(str, string.len(str) )
        if end_char == ' ' or end_char == '\t' or end_char == '\r' or end_char == '\n' then
            str = string.sub(str, 1, -2)
        else
            break
        end
    end
    return str
end

-- ���ַ���str���ַ���k���֣��������table��ʽ���ء�
-- table��key�Ǵ�1��ʼ��֤�飬value��str�б����ֺ���Ӵ���
function StringSplit(str, k)
    local now_count = 0
    local now_index = 1
    result = {}
    while now_index <= string.len(str) do
        match_begin, match_end = string.find(str, k, now_index)
        now_count = now_count + 1
        if type(match_begin) ~= "number" then -- not found more seperator
            result[now_count] = string.sub(str, now_index, string.len(str))
            break
        else
            result[now_count] = string.sub(str, now_index, match_begin - 1)
            now_index = match_end + 1
        end
    end
    return result
end
