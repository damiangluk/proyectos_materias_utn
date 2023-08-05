using System.Collections.Generic;
using System.Linq;
using System.IO;

namespace TPINTEGRADOR.Models
{
	public class Validador
	{
		private readonly List<Func<string, (bool, string)>> Validaciones;

		private static readonly Validador Verificador = new Validador();
		private static readonly int CantidadMinimaCaracteres = 8;

		private Validador()
		{
			Validaciones = new List<Func<string, (bool, string)>>
			{
				noEsClaveComun,
				tieneMinimoDeCaracteres
			};
		}

		public static Validador GetVerificador()
		{
			return Verificador;
		}

		#region public methods
		public (bool, string) EsClaveSegura(string password)
		{
			List<(bool, string)> resultados = Validaciones.Select(validacion => validacion(password)).ToList();
			if (resultados.All(r => r.Item1))
				return (true, string.Empty);
			else
				return (false, resultados.FirstOrDefault(r => !r.Item1).Item2);
		}

		public string GenerarContraseniaSugerida()
		{
			var random = new Random();
			var lengthPassword = random.Next(8, 64);
			const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!#$%&()*+,-./:;<=>?@[\\]^_`{|}~";
			string password;
			do
			{
				password = new string(Enumerable.Repeat(chars, lengthPassword).Select(s => s[random.Next(s.Length)]).ToArray());
			} while (!EsClaveSegura(password).Item1);

			return password;
		}
		#endregion

		#region private methods
		private (bool, string) noEsClaveComun(string password)
		{
			string message = $"La contraseña ingresada no debe ser comun";
			string rutaArchivo = "./static/claves_comunes.txt";
			string contenidoArchivo = File.ReadAllText(rutaArchivo);
			List<string> clavesComunes = contenidoArchivo.Split(new string[] { "\n", "\r\n" }, StringSplitOptions.None).ToList();
			return (!clavesComunes.Contains(password), message);
		}

		private (bool, string) tieneMinimoDeCaracteres(string password)
		{
			string message = $"La contraseña debe tener un minimo de {CantidadMinimaCaracteres} caracteres";
			return (!string.IsNullOrEmpty(password) && password.Length >= CantidadMinimaCaracteres, message);
		}
		#endregion
	}
}
