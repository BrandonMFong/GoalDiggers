using System;
using System.IO;
using System.Net;
using System.Text;
using System.Windows.Forms;
//using System.Windows.Forms; // C:\Windows\Microsoft.NET\assembly\GAC_MSIL\System.Windows.Forms\v4.0_4.0.0.0__b77a5c561934e089
using HtmlAgilityPack; // https://www.c-sharpcorner.com/UploadFile/9b86d4/getting-started-with-html-agility-pack/
using SHDocVw;
using Microsoft.PowerShell.Commands.Utility;
using mshtml;

namespace QuAD
{

    class Relay
    {
        static void Main(string[] args)
        {
            // Init variables
            string LocationUrl = "https://www.iplocation.net/";
            string LocationString = "", City = "", State = "";

            string test = OpenBrowser(LocationUrl);

            //var Locationdoc = new HtmlAgilityPack.HtmlDocument();
            //Locationdoc.LoadHtml(GetHTML(LocationUrl));

            //foreach (HtmlNode node in Locationdoc.DocumentNode.SelectNodes("//table[@class='iptable']"))
            //{
            //    foreach (HtmlNode tr in node.SelectNodes("tr"))
            //    {
            //        if(tr.SelectSingleNode("th").InnerText == "IP Location")
            //        {
            //            LocationString = tr.SelectSingleNode("td").InnerText;
            //            if(LocationString.Contains("&nbsp"))
            //            {
            //                LocationString = LocationString.Substring(0, LocationString.IndexOf("&nbsp")); // takes out redundant strings
            //            }
            //            break;
            //        }
            //    }
            //}
            //if (LocationString.Equals("")) throw new Exception("Something bad happened");
            ////https://www.airnow.gov/?city=Santa%20Rosa&state=California%20(US)

            //string[] LocationArray = LocationString.Split(",");
            //// Assuming the city is the first index 
            //City = LocationArray[0];
            //State = LocationArray[1];

            //string AQIUrl = "https://www.airnow.gov/?city=" + City + "&state=" + State;


            //var AQIDoc = new HtmlAgilityPack.HtmlDocument();
            //Locationdoc.LoadHtml(GetHTML(AQIUrl));
            //int AQI = 0; double TempF = 0.00;

            //// scan for AQI
            //foreach (HtmlNode node in Locationdoc.DocumentNode.SelectNodes("//div[@class='aqi']"))
            //{
            //    string nodestring = node.SelectSingleNode("b").InnerText;
            //    if (nodestring.Contains("NowCast AQI"))
            //    {
            //        AQI = Int32.Parse(nodestring);
            //        break;
            //    }
            //}
            //if (AQI == 0) { Console.WriteLine("AQI is empty"); }

            //// scan for tempf
            //foreach (HtmlNode node in Locationdoc.DocumentNode.SelectNodes("//div[@class='aqi']"))
            //{
            //    string nodestring = node.SelectSingleNode("b").InnerText;
            //    if (nodestring.Contains("NowCast AQI"))
            //    {
            //        AQI = Int32.Parse(nodestring);
            //        break;
            //    }
            //}
            //if (TempF == 0.00) { Console.WriteLine("Temperature is empty"); }
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
        static public string OpenBrowser(string url)
        {
            object o = null;
            SHDocVw.InternetExplorer ie = new SHDocVw.InternetExplorerClass();
            IWebBrowserApp wb = (IWebBrowserApp)ie;
            wb.Visible = false;
            //Do anything else with the window here that you wish
            wb.Navigate(url, ref o, ref o, ref o, ref o);
            mshtml.IHTMLDocument2 htmlDoc = wb.Document as mshtml.IHTMLDocument2;
            ie.Quit();
            return htmlDoc.body.outerHTML;
        }
    }
}
