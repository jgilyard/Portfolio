import json
import urllib2
import urllib
def data(stock_name):
    url = "http://finance.yahoo.com/d/quotes.csv?s=" +stock_name+"&f=nl1"
#    try:
    urllib.urlretrieve(url,stock_name+".csv")
#    except urllib.ContentTooShortError as e:    
#        outfile = open(stock_name + ".csv","w")
#        outfile.write(e.content)
#        outfile.close()
