
namespace TPINTEGRADOR.Models
{
    public abstract class Medio
    {
        public Medio(string contacto) 
        {
            Contacto = contacto;
        }

        public string Contacto;

        public abstract void Notificar(string mensaje, Persona persona);
    }
}
