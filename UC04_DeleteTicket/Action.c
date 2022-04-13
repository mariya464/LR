Action()
{
	lr_start_transaction("UC04_DeleteTicket");

	lr_start_transaction("open_site");
	
	web_reg_find("Text/IC=Web Tours",
		LAST);

	web_set_sockets_option("SSL_VERSION", "AUTO");

	web_add_auto_header("Sec-Fetch-Site", 
		"none");

	web_add_auto_header("Sec-Fetch-Dest", 
		"document");

	web_add_auto_header("Sec-Fetch-Mode", 
		"navigate");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	web_add_auto_header("sec-ch-ua", 
		"\" Not A;Brand\";v=\"99\", \"Chromium\";v=\"99\", \"Google Chrome\";v=\"99\"");

	web_add_auto_header("sec-ch-ua-mobile", 
		"?0");

	web_add_auto_header("sec-ch-ua-platform", 
		"\"Windows\"");

/*Correlation comment - Do not change!  Original value='133527.827865533ziziDDHpztfiDDDDtVcVApAcfiHf' Name ='userSession' Type ='ResponseBased'*/
	web_reg_save_param_attrib(
		"ParamName=userSession",
		"TagName=input",
		"Extract=value",
		"Name=userSession",
		"Type=hidden",
		SEARCH_FILTERS,
		"IgnoreRedirections=No",
		"RequestUrl=*/nav.pl*",
		LAST);

	web_url("WebTours", 
		"URL=http://localhost:1080/WebTours/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("open_site",LR_AUTO);

	lr_start_transaction("login");
	
	web_reg_find("Text/IC=User password was correct",
		LAST);

	web_revert_auto_header("Sec-Fetch-User");

	web_add_auto_header("Sec-Fetch-Dest", 
		"frame");

	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_add_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Sec-Fetch-Site", 
		"same-origin");

	lr_think_time(6);

	web_submit_data("login.pl",
		"Action=http://localhost:1080/cgi-bin/login.pl",
		"Method=POST",
		"TargetFrame=body",
		"RecContentType=text/html",
		"Referer=http://localhost:1080/cgi-bin/nav.pl?in=home",
		"Snapshot=t2.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=userSession", "Value={userSession}", ENDITEM,
		"Name=username", "Value={login}", ENDITEM,
		"Name=password", "Value={password}", ENDITEM,
		"Name=login.x", "Value=64", ENDITEM,
		"Name=login.y", "Value=12", ENDITEM,
		"Name=JSFormSubmit", "Value=off", ENDITEM,
		LAST);

	lr_end_transaction("login",LR_AUTO);

	lr_start_transaction("click_itinerary");
	
	web_reg_find("Text/IC=User wants the intineraries",
		LAST);
	
	web_reg_save_param("flightID",
	                   "LB/IC=name=\"flightID\" value=\"",
	                   "RB/IC=\"",
	                   "Ord=ALL",
	                   LAST);


	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	lr_think_time(16);
	


	web_url("Itinerary Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=itinerary", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);
	


	lr_end_transaction("click_itinerary",LR_AUTO);

	lr_start_transaction("delete_ticket");
	

	web_add_header("Origin", 
		"http://localhost:1080");
	
	web_add_auto_header("Sec-Fetch-User", 
		"?1");
	

	lr_think_time(17);
	
	if (atoi(lr_eval_string("{flightID_count}")) > 1){
		
		web_reg_find("Fail=Found",
		             "Text/IC={flightID_1}",
		             LAST);
		
		web_reg_find("Fail=Found",
		             "Text/IC={flightID_2}",
		             LAST);
		
		
		web_submit_form("itinerary.pl",
		    "Snapshot=t4.inf",
		    ITEMDATA,
		    "Name=1", "Value=on", ENDITEM,	
            "Name=2", "Value=on", ENDITEM,            
		    "Name=removeFlights.x", "Value=78", ENDITEM, 
		    "Name=removeFlights.y", "Value=6", ENDITEM, 
		    LAST);
		                
		                
	}
	
	else if (atoi(lr_eval_string("{flightID_count}")) == 1){
		
		web_reg_find("Fail=Found",
		"Text/IC={flightID_1}",
		LAST);
		

		
		web_submit_form("itinerary.pl",
		    "Snapshot=t4.inf",
		    ITEMDATA,
		    "Name=1", "Value=on", ENDITEM,			
		    "Name=removeFlights.x", "Value=78", ENDITEM, 
		    "Name=removeFlights.y", "Value=6", ENDITEM, 
		    LAST);
	
	}

	lr_end_transaction("delete_ticket",LR_AUTO);

	lr_start_transaction("click_sign_off");
	
	web_reg_find("Text/IC=A Session ID has been created and loaded into a cookie called MSO",
		LAST);

	web_revert_auto_header("Sec-Fetch-User");

	web_add_header("Sec-Fetch-User", 
		"?1");

	lr_think_time(25);

	web_url("SignOff Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=itinerary", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("click_sign_off",LR_AUTO);
	lr_end_transaction("UC04_DeleteTicket", LR_AUTO);

	return 0;
}