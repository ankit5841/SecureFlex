#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <curl/curl.h>

void innit()
{
	srand(time(NULL));
}
void store_ascii(char message[],int size,int ascii[])
{
	int i;
	
	for(i=0;i<size;i++)
	{
		ascii[i]=message[i];
		
	}
}

void random_key (int size, int random[], int ascii[])
{
	int i;
    for (i=0;i<size;i++)
    {
    	random[i]=rand()%95; //since I want random numbers between 0 and 94;
	}
	
	//adding random increment in ascii values;
	for (i=0;i<size;i++)
	{
		if((ascii[i]+random[i])>126)
		{
			ascii[i]=((ascii[i]+random[i])%126)+32;
		}
		else
		{
			ascii[i]=ascii[i]+random[i];
		}
	}
}

void send_encrypted(int ascii[],int size)
{
	char string[size];
	int i;
	for(i=0;i<size;i++)
	{
		string[i]=(char)ascii[i];
	}
	printf("\n");
	
	
	CURL *curl;
	CURLcode res;

	curl_global_init(CURL_GLOBAL_DEFAULT);

	curl = curl_easy_init();
	

	if(curl) {
		// Twilio Account SID and Auth Token
		const char *account_sid = "";
		const char *auth_token = "";

		// Twilio phone number and recipient phone number
		const char *from_number = "";
		const char *to_number = "";

		
		char message[100];
		snprintf(message, sizeof(message), "The Encrypted Text: %s", string);


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

		//curl_easy_setopt(curl, CURLOPT_URL, url)com;
		//curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data)comm;
		//curl_easy_setopt(curl, CURLOPT_USERPWD, auth_token)comm;
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
	printf("Encrypted Text Sent Successfully\n");
	getch();
	
	
	
}

void key_creation(int random[],int size)
{	
	FILE *file;
	file=fopen("KEY.txt","w");
	int i;
	for(i=0;i<size;i++)
	{
		if(random[i]<10)
		fprintf(file,"0%d",random[i]);
		else
		fprintf(file,"%d",random[i]);
	}
	
	fclose(file);	
}

void OTP()
{
	int OTP=(rand()%8998)+1000;
	FILE *file;
	file=fopen("OTP.txt","w");
	
	fprintf(file,"%d",OTP);
	fclose(file);
	
	CURL *curl;
	CURLcode res;

	curl_global_init(CURL_GLOBAL_DEFAULT);

	curl = curl_easy_init();
	

	if(curl) {
		// Twilio Account SID and Auth Token
		const char *account_sid = "AC688ea0abdc5c33c35838b0c945e057ee";
		const char *auth_token = "1edd1c0789572b45e105042bbedc667b";

		// Twilio phone number and recipient phone number
		const char *from_number = "+13345090442";
		const char *to_number = "+918510008485";

		// Message to send
		//const char *message ="Your OTP is 1126";
		
		char message[100];
		snprintf(message, sizeof(message), "Your OTP is %d", OTP);


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
	printf("OTP SENT SUCCESSFULLY\n");
}

void print(int ascii[],int size)
{
	
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
	char message[2000];
	printf("Enter the Message\n");
	gets(message);
	
	//start=clock();
	int size=strlen(message);
	int ascii[size];
	int random[size];
	
	innit();
	store_ascii(message,size,ascii);
	random_key(size,random,ascii);
	
	 
	system("CLS");
	printf("\nEncrypted Text\n\n");
	print(ascii,size);
	getch();
	send_encrypted(ascii,size);
	system("CLS");
	printf("Sending OTP\n");
	
	//end=clock();
	//printf("Time taken to encrypt %.0f ms\n",((double)(end-start)/CLOCKS_PER_SEC)*1000);

	
	int i=0;
	
//	for(i=0;i<size;i++)
//	{
//		printf("%d\n",random[i]);
//	}
	key_creation(random,size);	
	getch();
	OTP();
	
	
	
	return 0;
}
