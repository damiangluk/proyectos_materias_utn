
namespace TPINTEGRADOR.Models
{
    public class Participacion : Identidad
    {
        public Participacion(Persona persona, Comunidad comunidad, Rol rol, Medio medio)
        {
            Persona = persona;
            Comunidad = comunidad;
            Rol = rol;
            Medio = medio;
        }

        public Persona Persona;
        public Comunidad Comunidad;
        public Rol Rol;
        public Medio Medio;

        public void NotificarIncidente(Incidente incidente)
        {
            Medio.Notificar(incidente.Informe, Persona);
        }

        public void cambiarRol(Rol rol) {
            Rol = rol;
        }
    }
}