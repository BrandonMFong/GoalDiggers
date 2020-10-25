using System;
using System.IO;
using System.Net;
using System.Text;
using HtmlAgilityPack; // https://www.c-sharpcorner.com/UploadFile/9b86d4/getting-started-with-html-agility-pack/
using OpenQA.Selenium;
using OpenQA.Selenium.Firefox;
using System.Xml.Serialization;

namespace QuAD
{
    [XmlRoot("QuAD")]
    public class QuAD // Define config structure
    {
        public string WebServerIP { get; set; }
    }
    class Relay
    {
        static void Main(string[] args)
        {
            // Init variables
            string LocationUrl = "https://www.iplocation.net/";
            string LocationString = "", City, State;
            int AQI = 0; int TempF = 0; // define nodemcu important variables
            var Locationdoc = new HtmlAgilityPack.HtmlDocument(); // object to get Location site based off of IP 
            //System.Environment.SetEnvironmentVariable("webdriver.gecko.driver", "B:\\SOURCE\\Repo\\GoalDiggers\\Relay\\geckodriver.exe");
            //https://www.toolsqa.com/selenium-c-sharp/
            var fileStream = File.Open("config.xml", FileMode.Open);
            XmlSerializer serializer = new XmlSerializer(typeof(QuAD));
            var config = (QuAD)serializer.Deserialize(fileStream);
            string ipaddress = config.WebServerIP; // get ip from config

            while (true)
            {
                // define the driver that will process the http request
                IWebDriver driver = new FirefoxDriver(); // reopens a closed on
                Locationdoc.LoadHtml(GetHTML(LocationUrl));

                // Scan for location 
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

                string[] LocationArray = LocationString.Split(","); // assuming only one comma
                                                                    // Assuming the city is the first index 
                City = LocationArray[0];
                State = LocationArray[1];

                string AQIUrl = "https://www.airnow.gov/?city=" + City + "&state=" + State; // construct url for aqi url 


                driver.Url = AQIUrl; // request AQI site

                // Get AQI
                IWebElement elem = driver.FindElement(By.ClassName("aqi"));
                IWebElement AQIValElem = elem.FindElement(By.TagName("b"));
                AQI = Int32.Parse(AQIValElem.GetAttribute("innerHTML").ToString());

                // Get Temp
                IWebElement TempValElem = driver.FindElement(By.ClassName("weather-value"));
                TempF = Int32.Parse(TempValElem.GetAttribute("innerHTML").ToString());

                string nodeUrlstring = "http://" + ipaddress + "/Values?AQI=" + AQI.ToString() + "&TempF=" + TempF.ToString(); // construct string

                driver.Url = nodeUrlstring; // request nodemcu web server 
                driver.Quit();

                System.Threading.Thread.Sleep(5000);
            }
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
