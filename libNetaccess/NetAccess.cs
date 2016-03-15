using System;
using System.Text.RegularExpressions;
using System.Threading;
using RestSharp;

namespace libNetaccess
{
    public class NetAccess
    {
        public string Magic;
        public string InitUri;
        public string KeepaliveUrl;
        public string LogoutUrl;

        private readonly bool _loggedIn;

        public NetAccess(string username, string password)
        {
            var client = new RestClient("http://www.bing.com");
            var request = new RestRequest(Method.GET);
            var response = client.Execute(request);

            _loggedIn = false;
            InitUri = response.ResponseUri.ToString();
            Magic = Regex.Match(response.Content, @"""magic"" value=""(?<mgc>.+?)""").Groups["mgc"].Value;

            if (string.IsNullOrWhiteSpace(Magic))
                return;
           
            client = new RestClient("http://netaccess1.iitm.ac.in:1000");
            request = new RestRequest(Method.POST);
            request.AddHeader("Referer", InitUri);

            request.AddParameter("4Tredir", "http://google.com", ParameterType.GetOrPost);
            request.AddParameter("magic", Magic, ParameterType.GetOrPost);
            request.AddParameter("username", username, ParameterType.GetOrPost);
            request.AddParameter("password", password, ParameterType.GetOrPost);
            request.Timeout = Timeout.Infinite;
            response = client.Execute(request);

            KeepaliveUrl = Regex.Match(response.Content, @"location.href=""(?<url>.+keepalive.+?)""").Groups["url"].Value;
            LogoutUrl = Regex.Match(response.Content, @"location.href=""(?<url>.+logout.+?)""").Groups["url"].Value;

            if (!string.IsNullOrWhiteSpace(KeepaliveUrl + LogoutUrl))
                _loggedIn = true;
        }

        public bool LogOut()
        {
            var logoutResult = new RestClient(LogoutUrl).Get(new RestRequest()).Content;
            return logoutResult.Contains("logged out");
        }

        ~NetAccess()
        {
            if (!_loggedIn) return;
            var logoutResult = new RestClient(LogoutUrl).Get(new RestRequest()).Content;
            Console.WriteLine(logoutResult);
        }
    }
}
