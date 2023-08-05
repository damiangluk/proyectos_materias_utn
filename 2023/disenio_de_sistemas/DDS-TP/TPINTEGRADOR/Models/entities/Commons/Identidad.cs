using Microsoft.AspNetCore.Identity;

namespace TPINTEGRADOR.Models
{
    public class Identidad
    {
        public int Id = 0;

        public bool Equals(object obj)
        {
            return obj != null && obj is Identidad castObj && !Id.Equals(0) && Id.Equals(castObj.Id);
        }
    }
}
