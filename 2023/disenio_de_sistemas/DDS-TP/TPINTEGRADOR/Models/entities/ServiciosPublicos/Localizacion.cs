
using Microsoft.AspNetCore.Identity;

namespace TPINTEGRADOR.Models
{
    public class Localizacion : Identidad
    {
        public Localizacion(TipoLocalizacion tipo, string nombre) 
        {
            TipoLocalizacion = tipo;
            Nombre = nombre;
        }

        public TipoLocalizacion TipoLocalizacion;
        public string Nombre;
    }
}
