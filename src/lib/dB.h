#ifndef DB_H
#define DB_H

class dB {
  public:
    dB(long double);
    dB(const dB&);
    operator long double();

    long double in_dB() const;
    long double in_Linear() const;
  private:
    long double value_dB;
    long double value_Linear;
};

#endif // DB_H
