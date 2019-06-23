using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.Windows;

namespace Client
{
    public enum Codes
    {
        Signup = 100,
        Login,
        Logout,
        Create_Room,
        Join_Room,
        Get_Rooms,
        Get_Room_State,
        Leave_Room,
        Start_Game,
        Get_Question,
        Submit_Answer,
        Get_Statistics,
        Leave_Game,
        Success = 200,
        Error_Msg = 400
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
            SendToServer(((int)Codes.Login).ToString(), dict);
            //Irrelevant to return a string, 
            //If the function succeeds it has no meaning and if it fails it is caught in the exception
            ReceiveFromServer();
        }

        public void SignUp(string username, string password, string email)
        {
            Dictionary<string, object> dict = new Dictionary<string, object>();
            dict.Add("username", username);
            dict.Add("password", password);
            dict.Add("email", email);
            SendToServer(((int)Codes.Signup).ToString(), dict);
            //Again, no point to return a string
            ReceiveFromServer();
        }

        public string SignOut()
        {
            SendToServer(((int)Codes.Logout).ToString(), null);
            return ReceiveFromServer();
        }

        public int CreateRoom(string roomName, int maxPlayers, int questionCount, int timePerQuestion, int type)
        {
            Dictionary<string, object> dict = new Dictionary<string, object>();
            dict.Add("room_name", roomName);
            dict.Add("max_players", maxPlayers);
            dict.Add("question_count", questionCount);
            dict.Add("time_per_question", timePerQuestion);
            dict.Add("type", type);
            SendToServer(((int)Codes.Create_Room).ToString(), dict);
            return JsonConvert.DeserializeObject<Dictionary<string, int>>(ReceiveFromServer())["room_id"];
        }

        public void JoinRoom(int roomId)
        {
            Dictionary<string, object> dict = new Dictionary<string, object>();
            dict.Add("room_id", roomId);
            SendToServer(((int)Codes.Join_Room).ToString(), dict);
            ReceiveFromServer();
        }

        public List<Dictionary<string,object>> GetRooms()
        {
            SendToServer(((int)Codes.Get_Rooms).ToString(), null);
            return JsonConvert.DeserializeObject<List<Dictionary<string, object>>>(ReceiveFromServer());
        }

        public Dictionary<string,object> GetRoomState(int roomId)
        {
            Dictionary<string, object> dict = new Dictionary<string, object>();
            dict.Add("room_id", roomId);
            SendToServer(((int)Codes.Get_Room_State).ToString(), dict);
            return JsonConvert.DeserializeObject<Dictionary<string,object>>(ReceiveFromServer());
        }
        public void LeaveRoom(int roomId)
        {
            Dictionary<string, object> dict = new Dictionary<string, object>();
            dict.Add("room_id", roomId);
            SendToServer(((int)Codes.Leave_Room).ToString(), dict);
            ReceiveFromServer();
        }
        public void StartGame(int roomId)
        {
            Dictionary<string, object> dict = new Dictionary<string, object>();
            dict.Add("room_id", roomId);
            SendToServer(((int)Codes.Start_Game).ToString(), dict);
            ReceiveFromServer();
        }
        public Dictionary<string,object> GetQuestion(int number)
        {
            Dictionary<string,object> dict = new Dictionary<string, object>();
            dict.Add("number", number);
            SendToServer(((int)Codes.Get_Question).ToString(), dict);
            return JsonConvert.DeserializeObject<Dictionary<string, object>>(ReceiveFromServer());
        }
        public Dictionary<string,object> SubmitAnswer(int index, int number)
        {
            Dictionary<string, object> dict = new Dictionary<string, object>();
            dict.Add("index", index);
            dict.Add("number", number);
            SendToServer(((int)Codes.Submit_Answer).ToString(), dict);
            return JsonConvert.DeserializeObject<Dictionary<string, object>>(ReceiveFromServer());
        }
        public void LeaveGame(int gameId)
        {
            Dictionary<string, object> dict = new Dictionary<string, object>();
            dict.Add("game_id", gameId);
            SendToServer(((int)Codes.Leave_Game).ToString(), dict);
            ReceiveFromServer();
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
            if (code == (int)Codes.Error_Msg) //If there's an error, throw an exception, if not, the code is 200 for sure, so we only need to return the message.
                throw new Exception(msg);
            return msg == "null" ? "" : msg;
        }

        public void Close()
        {
            socket.Close();
        }
    }
   
}
