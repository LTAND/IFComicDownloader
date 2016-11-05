----------------------------------------------------------------------------------------------------
--  IFComicDownload��lua�ű����ز��Թ��� ver 2.0
--  2016-11-5 12:24:48 by seedjyh@gmail.com
----------------------------------------------------------------------------------------------------
-- ����ű��ļ������ṩ�Ľӿ�ֻ��һ����SiteDownloadURL
-- ���幦�ܼ��ú�����ͷ��ע�͡�

----------------------------------------------------------------------------------
-- ���к������վ�ű�������Ҫ�����͸�վ�йأ�����Դ���洢�����·���ڡ�
s_site_path = 'M:\\GitHubRepositories\\IFComicDownloader\\test-lua\\g.e-hentai.org\\'
-- ���л����ڱ��ص���ҳ�ļ��������·���ڡ��������Ա����ظ����ء�
s_page_path = s_site_path .. 'web\\page\\'
-- ���潫URL����ҳ�����ļ���ӳ���ϵ�洢�����ű���s_map_url_to_page_file��
s_map_url_to_page_file = {}
s_map_url_to_page_file['http://g.e-hentai.org/g/224263/e06fcdd082/'] = s_page_path .. 'comic_page.html'
s_map_url_to_page_file['http://g.e-hentai.org/g/224263/e06fcdd082/'] = s_page_path .. 'volume_page_home.html'
s_map_url_to_page_file['http://g.e-hentai.org/g/224263/e06fcdd082/?p=1'] = s_page_path .. 'volume_page_extra_1.html'
s_map_url_to_page_file['http://g.e-hentai.org/g/224263/e06fcdd082/?p=2'] = s_page_path .. 'volume_page_extra_2.html'
----------------------------------------------------------------------------------

-- ģ������һ����ҳ��ʵ�����Ǵ�pageĿ¼���ļ���
-- ������url�������ص���ҳURL��
-- ���أ�������URLû��Ԥ�赽ӳ��������޷��򿪲���ȡ��URLӳ�䵽�ı���·���ļ����򷵻�nil���ڶ�����������һ���ַ���˵������ԭ��
function DownloadURL(url, ref_url, cookies)
    FUNCTION_NAME='SiteDownloadURL(url=\'' .. url .. '\')'
    
    local file_path = s_map_url_to_page_file[url]
    if not file_path then
        return nil, FUNCTION_NAME .. ': No related file path from this URL'
    end

    local file_data, errmsg = ReadFile(file_path)
    if not file_data then
        return nil, FUNCTION_NAME .. ': cannot read file (path=\'' .. file_path .. '\'), because: ' .. errmsg
    end
    
    return file_data
end
