using System.Collections.Generic;
using System.Linq;
using System.IO;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;
using System.Text;
using static System.Runtime.InteropServices.JavaScript.JSType;

namespace TPINTEGRADOR.Models
{
    public class ConsultaAPI
    {
        public async Task<List<HttpResponseMessage>> ConsultarPOST(List<string> urls, List<object> data)
        {
            HttpClient httpClient = new HttpClient();

            List<HttpResponseMessage> responses = new List<HttpResponseMessage>();

            int i = 0;
            foreach (var url in urls)
            {
                var request = new HttpRequestMessage
                {
                    Method = HttpMethod.Post,
                    RequestUri = new Uri($"https://apis.datos.gob.ar/georef/api/{url}"),
                    Content = new StringContent(JsonConvert.SerializeObject(data[i]), Encoding.UTF8, "application/json")
                };

                var response = await httpClient.SendAsync(request);
                responses.Add(response);
                i++;
            }

            return responses;
        }
    }

}
