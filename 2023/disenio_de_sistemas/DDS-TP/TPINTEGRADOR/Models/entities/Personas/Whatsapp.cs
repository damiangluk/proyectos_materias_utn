
namespace TPINTEGRADOR.Models
{
    public class Whatsapp : Medio
    {
        public Whatsapp(string contacto) : base(contacto)
        {

        }

        public override void Notificar(string mensaje, Persona persona)
        {
            // Enviar whatsapp a la PERSONA al telefono de CONTACTO con el MENSAJE
        }
    }
}
