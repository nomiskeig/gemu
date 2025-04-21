#include <cstdint>

using Reg8Val = int8_t;
class Interrupts {
  private:
    Reg8Val ie;
    Reg8Val i_f;

  public:
    void setIE(Reg8Val i_e);
    void setIF(Reg8Val i_f);
    Reg8Val getIE();
};
