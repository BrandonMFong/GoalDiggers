using System;
using System.IO;
using System.Net;
using System.Text;
using System.Windows.Forms; // C:\Windows\Microsoft.NET\assembly\GAC_MSIL\System.Windows.Forms\v4.0_4.0.0.0__b77a5c561934e089

namespace QuAD
{
    class Relay
    {
        static void Main(string[] args)
        {
            // Init variables
            string LocationSite = "https://www.iplocation.net/";
            string City, State, Country;

            string LocationHTML = GetHTML(LocationSite);
            HtmlDocument resultat = new HtmlDocument();

        }

        /// <summary>
        /// Returns HTML in string format
        /// </summary>
        /// <param name="url"></param>
        /// <returns></returns>
        static string GetHTML(string url)
        {
            HttpWebRequest request = (HttpWebRequest)WebRequest.Create(url);
            HttpWebResponse response = (HttpWebResponse)request.GetResponse();
            string HTML = "";

            if (response.StatusCode == HttpStatusCode.OK)
            {
                Stream receiveStream = response.GetResponseStream();
                StreamReader readStream = null;

                if (String.IsNullOrWhiteSpace(response.CharacterSet))
                    readStream = new StreamReader(receiveStream);
                else
                    readStream = new StreamReader(receiveStream, Encoding.GetEncoding(response.CharacterSet));

                HTML = readStream.ReadToEnd(); // Contains HTML

                response.Close();
                readStream.Close();
            }
            else throw new Exception("Something bad happened");
            return HTML;
        }
    }
}
