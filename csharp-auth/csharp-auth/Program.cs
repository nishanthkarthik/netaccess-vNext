using System;
using libNetaccess;

namespace csharp_auth
{
    class Program
    {
        static void Main(string[] args)
        {
            string roll = Console.ReadLine();
            string passwd = Console.ReadLine();
            var net = new NetAccess(roll, passwd);
            Console.WriteLine(net.KeepaliveUrl);
            Console.WriteLine("> logged out : " + net.LogOut());
        }
    }
}
