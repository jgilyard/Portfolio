import json
import urllib2
import urllib
def data_prev(stock_name):
    url = "http://ichart.yahoo.com/table.csv?s="+stock_name+"&a=0&b=1&c=2000"
    urllib.urlretrieve(url, stock_name+"prev_.csv")


