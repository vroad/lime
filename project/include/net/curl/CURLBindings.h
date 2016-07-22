#include <hx/CFFIPrime.h>
#include <curl/curl.h>


namespace lime {
	
	value curl_easy_getinfo_wrap (CURL* curl, int info);
	
	value curl_easy_unescape_wrap (CURL* curl, HxString url);
	
	value curl_version_info_wrap (int type);
	
	CURL* val_to_CURL (value inHandle);
	
	value CURL_to_val (CURL* inInstance);
	
	
}