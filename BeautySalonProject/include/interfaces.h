#ifndef INTERFACES_H
#define INTERFACES_H

namespace Beauty_Salon {
    // Interfata pentru obiecte care pot primi reduceri
    class IDiscountable {
    public:
        virtual ~IDiscountable() = default;
        
        // Aplică un discount la o sumă data
        virtual double ApplyDiscount(double amount) = 0;
    };

    // Interfata pentru obiecte care pot fi programate în timp
    class ISchedulable {
    public:
        virtual ~ISchedulable() = default;
        
        // Obtine durata actiunii programabile
        virtual int GetDuration() const = 0;
        
        // Verifica dacă actiunea necesita un specialist
        virtual bool RequiresSpecialist() const = 0;
    };
}

#endif // INTERFACES_H