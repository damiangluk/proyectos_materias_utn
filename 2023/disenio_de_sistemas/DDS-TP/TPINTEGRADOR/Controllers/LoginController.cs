using Auth0.AspNetCore.Authentication;
using Microsoft.AspNetCore.Authentication;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Authentication.Cookies;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Rendering;
using System.Diagnostics;
using System.Security.Claims;
using TPINTEGRADOR.Models;


namespace TPINTEGRADOR.Controllers
{
    public class LoginController : Controller
    {
        private readonly ILogger<LoginController> _logger;

        public LoginController(ILogger<LoginController> logger)
        { 
            _logger = logger;
        }

        [System.Web.Mvc.HttpPost]
        public async Task LoginAuth(string returnUrl = "/")
        {
            string toMove = string.IsNullOrEmpty(returnUrl) ? Url?.Action("Index", "Home") ?? "" : returnUrl;
            var authenticationProperties = new LoginAuthenticationPropertiesBuilder()
                      .WithRedirectUri(Url?.Action("Index", "Home") ?? "")
                      .Build();
            await HttpContext.ChallengeAsync(Auth0Constants.AuthenticationScheme, authenticationProperties);

        }

        [Authorize]
        public async Task LogoutAuth()
        {
            var authenticationProperties = new LogoutAuthenticationPropertiesBuilder()
                .WithRedirectUri(Url?.Action("Login", "Login") ?? "")
                .Build();
            // Logout from Auth0
            await HttpContext.SignOutAsync(Auth0Constants.AuthenticationScheme, authenticationProperties);
            // Logout from the application
            await HttpContext.SignOutAsync(CookieAuthenticationDefaults.AuthenticationScheme);

        }
        #region routes

        public IActionResult Login()
        {
            ViewBag.ContraseniaSugerida = Validador.GetVerificador().GenerarContraseniaSugerida();

			return View();
        }

		[ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
        public IActionResult Error()
        {
            return View(new ErrorViewModel { RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier });
        }
        #endregion

        [HttpPost]
		public IActionResult Login(LoginViewModel model)
		{
            (bool, string) resultado = Validador.GetVerificador().EsClaveSegura(model.Password);
			if (resultado.Item1)
			{
				return RedirectToAction("Index", "Home");
			}
			else
			{
				ViewBag.ContraseniaSugerida = Validador.GetVerificador().GenerarContraseniaSugerida();
				ViewBag.MensajeError = resultado.Item2;
				return View("login", model);
			}
        }
    }
}