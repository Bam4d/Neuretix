/* 
 * File:   OnlineRandomNums.cpp
 * Author: bam4d
 * 
 * Created on 13 December 2010, 21:37
 */

#include "globals.h"

// This is the writer call back function used by curl
static int writer(char *data, size_t size, size_t nmemb,
                  std::string *buffer)
{
  // What we will return
  int result = 0;

  // Is there anything in the buffer?
  if (buffer != NULL)
  {
    // Append the data to the buffer
    buffer->append(data, size * nmemb);

    // How much did we write?
    result = size * nmemb;
  }

  return result;
}  

OnlineRandomNums::OnlineRandomNums() {

    CURL *curl;
    CURLcode res;
    static char errorBuffer[CURL_ERROR_SIZE];

    // Write all expected data in here
    static string buffer;
    curl = curl_easy_init();
    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "http://www.random.org/integers/?num=10&min=-1000000000&max=1000000000&col=1&base=16&format=plain&rnd=new");
        curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
        curl_easy_setopt(curl, CURLOPT_HEADER, 0);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        res = curl_easy_perform(curl);

        /* always cleanup */
        curl_easy_cleanup(curl);
    }


}

OnlineRandomNums::OnlineRandomNums(const OnlineRandomNums& orig) {
}

OnlineRandomNums::~OnlineRandomNums() {
}

