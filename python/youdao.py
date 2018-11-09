
# -*- coding: UTF-8 -*-
from urllib import request
from urllib import parse
import json

if __name__ == "__main__":
    Request_URL = 'http://fanyi.youdao.com/translate?smartresult=dict&smartresult=rule&smartresult=ugc&sessionFrom=https://www.baidu.com/link' 
    Form_Data = {} 
    Form_Data['type'] = 'AUTO' 
    Form_Data['i'] = 'Jack' 
    Form_Data['doctype'] = 'json' 
    Form_Data['xmlVersion'] = '1.8' 
    Form_Data['keyfrom'] = 'fanyi.web' 
    Form_Data['ue'] = 'ue:UTF-8' 
    Form_Data['action'] = 'FY_BY_CLICKBUTTON' 
    data = parse.urlencode(Form_Data).encode('utf-8') 
    response = request.urlopen(Request_URL,data) 
    html = response.read().decode('utf-8') 
    translate_results = json.loads(html) 
    translate_results = translate_results['translateResult'][0][0]['tgt'] 
    print("翻译的结果是：%s" % translate_results)
