using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace Client
{
    public enum Codes
    {
        SIGNUP = 100,
        LOGIN,
        LOGOUT,
        CREATE_ROOM,
        JOIN_ROOM,
        GET_ROOMS,
        GET_PLAYERS_IN_ROOM,
        SUCCESS = 200,
        ERROR_MSG = 300
    }

    public class SocketHandler
    {
        
        private NetworkStream socket;
        //Create a socket to use in the other functions
        public SocketHandler(string serverAddress, int serverPort)
        {
            TcpClient client = new TcpClient();
            IPEndPoint serverEndPoint = new IPEndPoint(IPAddress.Parse(serverAddress), serverPort);
            client.Connect(serverEndPoint);
            socket = client.GetStream();
        }

        public void SignIn(string username, string password) 
        {
            Dictionary<string, object> dict = new Dictionary<string, object>();
            dict.Add("username", username);
            dict.Add("password", password);
            SendToServer("101", dict);
            //Irrelevant to return a string, 
            //If the function succeeds it has no meaning and if it fails it is caught in the exception
            ReceiveFromServer();
        }

        public string SignUp(string username, string password, string email)
        {
            Dictionary<string, object> dict = new Dictionary<string, object>();
            dict.Add("username", username);
            dict.Add("password", password);
            dict.Add("email", email);
            SendToServer("100", dict);
            return ReceiveFromServer();
        }

        public string SignOut()
        {
            SendToServer("102", null);
            return ReceiveFromServer();
        }

        public string CreateRoom(string roomName, int maxPlayers, int questionCount, int timePerQuestion, int type)
        {
            Dictionary<string, object> dict = new Dictionary<string, object>();
            dict.Add("room_name", roomName);
            dict.Add("max_players", maxPlayers);
            dict.Add("question_count", questionCount);
            dict.Add("time_per_question", timePerQuestion);
            dict.Add("type", type);
            SendToServer("103", dict);
            return ReceiveFromServer();
        }

        public string JoinRoom(int roomId)
        {
            Dictionary<string, object> dict = new Dictionary<string, object>();
            dict.Add("room_id", roomId);
            SendToServer("104", dict);
            return ReceiveFromServer();
        }

        public List<Dictionary<string,object>> GetRooms()
        {
            SendToServer("105", null);
            string buffer = ReceiveFromServer();
            JArray jsonList = (JArray)JsonConvert.DeserializeObject(buffer);
            List<Dictionary<string, object>> list = jsonList.ToObject<List<Dictionary<string, object>>>();
            return list;
        }

        public string GetPlayersInRoom(int roomId)
        {
            Dictionary<string, object> dict = new Dictionary<string, object>();
            dict.Add("room_id", roomId);
            SendToServer("106", dict);
            return ReceiveFromServer();
        }

        private void SendToServer(string code, Dictionary<string, object> data)
        {
            
            List<byte> buffer = new ASCIIEncoding().GetBytes(JsonConvert.SerializeObject(data)).ToList();
            //Add code of message and length of json message, according to the protocol
            List<byte> prefix = Encoding.ASCII.GetBytes(code + buffer.Count.ToString().PadLeft(4, '0')).ToList();
            prefix.AddRange(buffer);
            byte[] bytes = prefix.ToArray();
            socket.Write(bytes, 0, bytes.Length);
            socket.Flush();
        }
        private string ReceiveFromServer()
        {
            string msg = "";
            byte[] bytes = new byte[3];
            int bytesRead = socket.Read(bytes, 0, bytes.Length);
            int code = int.Parse(Encoding.Default.GetString(bytes));
            bytes = new byte[4];
            bytesRead = socket.Read(bytes, 0, bytes.Length);
            int size = int.Parse(Encoding.Default.GetString(bytes));
            if (size != 0)
            {
                bytes = new byte[size];
                bytesRead += socket.Read(bytes, 0, bytes.Length);
                msg = Encoding.Default.GetString(bytes);
            }
            if (code == (int)Codes.ERROR_MSG) //If there's an error, throw an exception, if not, the code is 200 for sure, so we only need to return the message.
                throw new Exception(msg);
            return msg;
        }
    }
    class Rooms
    {
        public List<Dictionary<string, object>> list;
    }
}
