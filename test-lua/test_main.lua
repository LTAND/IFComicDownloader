----------------------------------------------------------------------------------------------------
--  IFComicDownload��lua�ű����ز��Թ��� ver 1.0
--  2016-9-5 13:19:37 by seedjyh@gmail.com
----------------------------------------------------------------------------------------------------
-- ����ļ��ǲ���lua�ű������ļ���
-- ����4����
-- 1. ����script/api/lua�ű����Լ�script/sites/www.XXX.com/*.lua�������ĸ�վ����Ҫָ�����ű���
-- 2. ��ȡһ��ָ����html�ļ�����������������ص����أ���
-- 3. ������Ҫ���Եĺ�������ֹһ����������Analyse��Get���������
----------------------------------------------------------------------------------------------------
dofile("M:\\GitHubRepositories\\IFComicDownloader\\test-lua\\test_tool.lua")

------------------------------------------------------------------
-- Ԥ�����
-- �����Ե���վĿ¼����λ��script/sites/�£�������'www.ikanman.com'
local site_dir = 'www.dm5.com'
-- ����������ҳ�ļ������Ѿ������ص�����Ӳ�̣�
local web_file_path = "M:\\GitHubRepositories\\IFComicDownloader\\test-lua\\comic_page.html"
-- ����������ҳURL
local web_page_url = "http://g.e-hentai.org/s/5ea57e66ac/523011-1"
------------------------------------------------------------------

-- Step 1���������д����Ի����ʱ���õ���lua�ű���
for _,v in pairs(GetRequiredLuaScriptList(site_dir)) do
    dofile(v)
end

-- Step 2�����ش����Ե���ҳ�ļ���
pagestr = ReadFile(web_file_path)

-- Step 3�����������Եĺ�����
--print(GetPageIndexFromURL(web_page_url))
print(ComicPageAnalyse(web_page_url, pagestr, ""))

-- END.

-- ע����Analyse�׶β������κ�ת�롣
-- ��Ϊת����Ҫ����C�⣬��Ŀǰ��û�п���lua�����뿪C���������C��Ĵ��롣
-- ת�����ڴӷ������Get���ݵ�ʱ���ǲ�����ʱ�����ԡ�
-- ��������������жϡ�
