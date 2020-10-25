using System;
using System.Reflection;
using System.IO;
using System.Net;
using System.Text;
using System.Windows.Forms;
//using System.Windows.Forms; // C:\Windows\Microsoft.NET\assembly\GAC_MSIL\System.Windows.Forms\v4.0_4.0.0.0__b77a5c561934e089
using HtmlAgilityPack; // https://www.c-sharpcorner.com/UploadFile/9b86d4/getting-started-with-html-agility-pack/
using SHDocVw;
using Microsoft.PowerShell.Commands.Utility;
using OpenQA.Selenium;
using OpenQA.Selenium.Firefox;

namespace QuAD
{

    class Relay
    {
        static void Main(string[] args)
        {
            // Init variables
            string LocationUrl = "https://www.iplocation.net/";
            string LocationString = "", City = "", State = "";

            var Locationdoc = new HtmlAgilityPack.HtmlDocument();
            Locationdoc.LoadHtml(GetHTML(LocationUrl));

            foreach (HtmlNode node in Locationdoc.DocumentNode.SelectNodes("//table[@class='iptable']"))
            {
                foreach (HtmlNode tr in node.SelectNodes("tr"))
                {
                    if (tr.SelectSingleNode("th").InnerText == "IP Location")
                    {
                        LocationString = tr.SelectSingleNode("td").InnerText;
                        if (LocationString.Contains("&nbsp"))
                        {
                            LocationString = LocationString.Substring(0, LocationString.IndexOf("&nbsp")); // takes out redundant strings
                        }
                        break;
                    }
                }
            }
            if (LocationString.Equals("")) throw new Exception("Something bad happened");
            //https://www.airnow.gov/?city=Santa%20Rosa&state=California%20(US)

            string[] LocationArray = LocationString.Split(",");
            // Assuming the city is the first index 
            City = LocationArray[0];
            State = LocationArray[1];

            string AQIUrl = "https://www.airnow.gov/?city=" + City + "&state=" + State;

            int AQI = 0; int TempF = 0;

            //System.Environment.SetEnvironmentVariable("webdriver.gecko.driver", "B:\\SOURCE\\Repo\\GoalDiggers\\Relay\\geckodriver.exe");
            //https://www.toolsqa.com/selenium-c-sharp/
            IWebDriver driver = new FirefoxDriver();
            driver.Url = AQIUrl;

            // Get AQI
            IWebElement elem = driver.FindElement(By.ClassName("aqi"));
            IWebElement AQIValElem = elem.FindElement(By.TagName("b"));
            AQI = Int32.Parse(AQIValElem.GetAttribute("innerHTML").ToString());

            // Get Temp
            IWebElement TempValElem = driver.FindElement(By.ClassName("weather-value"));
            TempF = Int32.Parse(TempValElem.GetAttribute("innerHTML").ToString());

            Console.WriteLine(TempF.ToString());
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
        //static public string OpenBrowser(string url)
        //{
        //    object o = null;
        //    SHDocVw.InternetExplorer ie = new SHDocVw.InternetExplorerClass();
        //    IWebBrowserApp wb = (IWebBrowserApp)ie;
        //    wb.Visible = false;
        //    //Do anything else with the window here that you wish
        //    wb.Navigate(url, ref o, ref o, ref o, ref o);
        //    mshtml.IHTMLDocument2 htmlDoc = wb.Document as mshtml.IHTMLDocument2;
        //    ie.Quit();
        //    return htmlDoc.body.outerHTML;
        //}
    }
}
