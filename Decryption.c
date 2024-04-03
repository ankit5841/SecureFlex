#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <time.h>

void store_ascii(char message[],int size,int ascii[])
{
	int i;
	
	for(i=0;i<size;i++)
	{
		ascii[i]=message[i];
		
	}
}
void store_random(char string[],int random[],int size)
{
	int j=0,temp=0,n=0;
	int i=0;
	for(i=0;i<size;i=i+2)
	{
		n=(int)string[i];
		n=n-48;
		temp=n;
		n=(int)string[i+1];
		n=n-48;
		temp=temp*10+n;
		random[j]=temp;
		j++;
		
	}
}
void decrypt(int ascii[],int random[],int size)
{
	int i;
	for(i=0;i<size;i++)
	{
		if ((ascii[i]-random[i])<32)
		{
			int x;
			if((ascii[i]-random[i])<0)
			{
				x=ascii[i]-random[i];
				ascii[i]=126+x-32;
				
			}
			else
			{
				x=ascii[i]-random[i];
				x=32-x;
				ascii[i]=126-x;
			}
		}
		else
		{
			ascii[i]=ascii[i]-random[i];
		}
		
	}

}
int verifyOTP(char OTP[])
{
	FILE *file;
	file=fopen("OTP.txt","r");
	char ch[5];
	fgets(ch,5,file);
	fclose;
	
	int i=0;
	for(i=0;i<4;i++)
	{
		if(ch[i]!=OTP[i])
		return 0;
	}
	return 1;
		
}

void keysender()
{
	char ch[20000];
	FILE *file;
	file=fopen("KEY.txt","r");
	fgets(ch,20000,file);
	fclose;
	
	CURL *curl;
	CURLcode res;

	curl_global_init(CURL_GLOBAL_DEFAULT);

	curl = curl_easy_init();
	

	if(curl) {
		// Twilio Account SID and Auth Token
		const char *account_sid = "";//Fill your Twilio Key
		const char *auth_token = "";//Fill your Twilio Token

		// Twilio phone number and recipient phone number
		const char *from_number = "";// Fill Ph.No.
		const char *to_number = "";// Fill Ph.No.

		// Message to send
		//const char *message ="Your OTP is 1126";
		
		char message[20000];
		snprintf(message, sizeof(message), "Your KEY is %s", ch);


		// Construct Twilio API URL
		char url[200];
		snprintf(url, sizeof(url), "https://api.twilio.com/2010-04-01/Accounts/AC688ea0abdc5c33c35838b0c945e057ee/Messages.json");

		// Construct POST data
		char post_data[500];
		snprintf(post_data, sizeof(post_data), "From=%s&To=%s&Body=%s", from_number, to_number, message);

		curl_easy_setopt(curl, CURLOPT_POST, 1);
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);
		curl_easy_setopt(curl, CURLOPT_USERNAME, account_sid);
		curl_easy_setopt(curl, CURLOPT_PASSWORD, auth_token);

		//curl_easy_setopt(curl, CURLOPT_URL, url);
		//curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);
		//curl_easy_setopt(curl, CURLOPT_USERPWD, auth_token);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);  // This disables SSL certificate verification


		// Send the HTTP POST request
		res = curl_easy_perform(curl);

		// Check for errors
		if(res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

		// Clean up
		curl_easy_cleanup(curl);
	}

	curl_global_cleanup();
	system("CLS");
	printf("KEY SENT SUCCESSFULLY\n");
}

void print(int ascii[],int size)
{
	
	system("CLS");
	printf("The Message is:\n\n");
	int i;
	for(i=0;i<size;i++)
	{
		printf("%c",ascii[i]);
	}
	printf("\n");

}

int main()
{
	clock_t start,end;
	char c[20000],key[20000];
	int ascii[20000],random[20000];
	char OTP[4];
	printf("Enter the OTP\n");
	scanf("%s",OTP);
	int a=verifyOTP(OTP);
	system("CLS");
	
	if(a==1)
	{
	printf("Authentication Successfull\nSending Key\n");	
	keysender();
	printf("\n\nEnter to continue\n");
	getch();
	system("CLS");
	printf("Enter The Encrypted Message\n");
	scanf("%s",&c);
	int size=strlen(c);
	//printf("%s",c);
	printf("Enter The Key\n");
	scanf("%s",key);



	//start=clock();

	store_ascii(c,size,ascii);
	store_random(key,random,size*2);
	decrypt(ascii,random,size*2);
	print(ascii,size);
	//end=clock();
	//printf("Time taken to decrypt %0.f ms",((double)(end-start)/CLOCKS_PER_SEC)*1000);
	
	}
	else
	{
		printf("OTP VERIFICATION FAILED\n");
		printf("\nWRONG OTP");
	}


	return 0;
}
