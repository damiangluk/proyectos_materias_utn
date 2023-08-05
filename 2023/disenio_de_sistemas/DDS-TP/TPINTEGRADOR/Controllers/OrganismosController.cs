using Microsoft.AspNetCore.Mvc;
using Newtonsoft.Json;
using System.ComponentModel.DataAnnotations.Schema;
using System.Diagnostics;
using System.Security.Cryptography;
using System.Text;
using TPINTEGRADOR.Models;

namespace TPINTEGRADOR.Controllers
{
    public class OrganismosController : Controller
    {
        private readonly ILogger<HomeController> _logger;

        public OrganismosController(ILogger<HomeController> logger)
        {
            _logger = logger;
        }

        public IActionResult Index()
        {
            return View();
        }

        [System.Web.Mvc.HttpPost]
        public async Task<string> ValidarArchivo(IFormFile archivoCSV)
        {
            SistemaServiciosPublicos system = SistemaServiciosPublicos.GetInstance;
            LectorCSV lectorCSV = new LectorCSV();
            List<string[]> rows = await lectorCSV.LeerArchivo(archivoCSV);
            if(!lectorCSV.Valido) 
            {
                object resultError = new
                {
                    status = true,
                    validation = false,
                    message = lectorCSV.Error,
                };

                return JsonHelper.SerializeObject(resultError, 4);
            }

            var rowsError = "";

            for(int i = 1; i < rows.Count; i++)
            {
                if (!system.AgregarOrganismo(rows[i]))
                    rowsError += (i + ",");
            }

            if (!string.IsNullOrEmpty(rowsError))
            {
                rowsError = "Las siguientes filas son invalidas: " + rowsError.Substring(0, rowsError.Length - 1);
            }

            object result = new
            {
                status = true,
                validation = true,
                content = new { 
                    rowsError,
                    organismos = system.Organismos.Select(org => org.OrganismosForFront()).ToList(),
                }
            };

            return JsonHelper.SerializeObject(result, 4);
        }

        private List<GeoApiParam> CargarParametros(List<string[]> rows) {
            var geoApiParams = new List<GeoApiParam>();

            var provincias = new GeoApiParam();
            var municipios = new GeoApiParam();
            var departamentos = new GeoApiParam();

            for (int i = 1; i < rows.Count; i++)
            {
                var row = rows[i];

                if (row[3] == "DEPARTAMENTO" && !departamentos.Param.Any(d => d.nombre == row[4]))
                {
                    departamentos.Param.Add(new Param
                    {
                        nombre = row[4],
                        campos = "id,nombre",
                        max = 1,
                        exacto = true
                    });
                }
                else if (row[3] == "MUNICIPIO" && !municipios.Param.Any(m => m.nombre == row[4]))
                {
                    municipios.Param.Add(new Param
                    {
                        nombre = row[4],
                        campos = "id,nombre",
                        max = 1,
                        exacto = true
                    });
                }
                else if (row[3] == "PROVINCIA" && !provincias.Param.Any(p => p.nombre == row[4]))
                {
                    provincias.Param.Add(new Param
                    {
                        nombre = row[4],
                        campos = "id,nombre",
                        max = 1,
                        exacto = true
                    });
                }
            }

            geoApiParams.Add(provincias);
            geoApiParams.Add(municipios);
            geoApiParams.Add(departamentos);

            return geoApiParams;
        }

        public async Task<Tuple<List<LocalizacionAPI>, List<LocalizacionAPI>, List<LocalizacionAPI>>> ConsultarAPI(List<GeoApiParam> parametros)
        {
            HttpClient httpClient = new HttpClient();

            List<string> urls = new List<string> { "provincias", "municipios", "departamentos" };

            List<object> data = new List<object> { new { provincias = parametros[0].Param }, new { municipios = parametros[1].Param }, new { departamentos = parametros[2].Param } };

            ConsultaAPI consulta = new ConsultaAPI();
            List<HttpResponseMessage> responses = await consulta.ConsultarPOST(urls, data);

            List<LocalizacionAPI> provinciasResult = new List<LocalizacionAPI>();
            List<LocalizacionAPI> departamentosResult = new List<LocalizacionAPI>();
            List<LocalizacionAPI> municipiosResult = new List<LocalizacionAPI>();

            GeoApiResponse? provinciasContent = JsonConvert.DeserializeObject<GeoApiResponse>(await responses[0].Content.ReadAsStringAsync());
            GeoApiResponse? municipiosContent = JsonConvert.DeserializeObject<GeoApiResponse>(await responses[1].Content.ReadAsStringAsync());
            GeoApiResponse? departamentosContent = JsonConvert.DeserializeObject<GeoApiResponse>(await responses[2].Content.ReadAsStringAsync());

            provinciasResult = provinciasContent != null ? provinciasContent.resultados
                .Where(res => res.cantidad > 0)
                .Select(res => res.provincias[0])
                .ToList() : new List<LocalizacionAPI>();

            municipiosResult = municipiosContent != null ? municipiosContent.resultados
                .Where(res => res.cantidad > 0)
                .Select(res => res.municipios[0])
                .ToList() : new List<LocalizacionAPI>();

            departamentosResult = departamentosContent != null ? departamentosContent.resultados
                .Where(res => res.cantidad > 0)
                .Select(res => res.departamentos[0])
                .ToList() : new List<LocalizacionAPI>();

            return new Tuple<List<LocalizacionAPI>, List<LocalizacionAPI>, List<LocalizacionAPI>>(provinciasResult, municipiosResult, departamentosResult);
        }

        [ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
        public IActionResult Error()
        {
            return View(new ErrorViewModel { RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier });
        }
    }
}