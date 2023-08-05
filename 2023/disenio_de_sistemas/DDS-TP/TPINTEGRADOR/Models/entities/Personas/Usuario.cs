
namespace TPINTEGRADOR.Models
{
    public class Usuario : Identidad
    {
        public Usuario(string correoElectronico, string contrasenia, bool activo, Persona persona)
        {
            CorreoElectronico = correoElectronico;
            Contrasenia = contrasenia;
            Activo = activo;
            Persona = persona;
        }

        public string CorreoElectronico;
        public string Contrasenia;
        public bool Activo;
        public Persona Persona;
    }
}