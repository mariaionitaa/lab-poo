#ifndef SERVICE_H
#define SERVICE_H

#include "Interfaces.h"
#include "Utils.h"
#include <string>
#include <iostream>
#include <vector>

namespace Beauty_Salon {
    // Clasa de baza pentru toate serviciile oferite de salon
    class Service : public IDiscountable, public ISchedulable {
    private:
        std::string m_name;            
        double m_base_price;           
        ServiceDetails m_details;      
        ServiceType m_type;            
        
    protected:
        // Metoda protejata pentru actualizarea detaliilor serviciului în subclase
        void _UpdateDetails(const ServiceDetails& details);
        
    public:
        // Membri statici
        static int m_total_services_booked;  
        
        // Metoda statica pentru obtinerea numarului de rezervari
        static int GetTotalBookings();
        
        // Constructori si destructor
        Service();
        Service(std::string name, double basePrice);
        Service(std::string name, double basePrice, int durationMinutes);
        Service(std::string name, double basePrice, const ServiceDetails& details);
        virtual ~Service();
        
        // Getteri 
        std::string GetName() const;
        double GetBasePrice() const;
        ServiceType GetType() const;
        const ServiceDetails& GetDetails() const;
        
        // Implementari ale metodelor din interfete
        virtual double ApplyDiscount(double amount) override;
        virtual int GetDuration() const override;
        virtual bool RequiresSpecialist() const override;
        
        // Metode virtuale care vor fi suprascrise în clasele derivate
        virtual double CalculatePrice() = 0;  
        virtual int EstimateTime() = 0;       
        virtual void DisplayInfo() const;
        
        // Supraincarcare operator pentru afisare
        friend std::ostream& operator<<(std::ostream& os, const Service& service);
    };

    // Clasa pentru servicii de par (tuns, vopsit, coafat)
    class HairService : public Service {
    private:
        bool m_includes_washing;     
        bool m_includes_styling;    
        
    public:
        // Constructori
        HairService();
        HairService(std::string name, double basePrice);
        HairService(std::string name, double basePrice, bool washing, bool styling);
        
        // Setteri
        void SetIncludesWashing(bool includes);
        void SetIncludesStyling(bool includes);
        
        // Getteri
        bool IncludesWashing() const;
        bool IncludesStyling() const;
        
        // Implementari ale metodelor virtuale
        virtual double CalculatePrice() override;
        virtual int EstimateTime() override;
        virtual void DisplayInfo() const override;
    };

    // Clasa pentru servicii de unghii (manichiura, pedichiura)
    class NailService : public Service {
    private:
        bool m_is_gel;        
        int m_nail_count;     // Numărul de unghii (de obicei 10, dar poate fi mai puțin)
        
    public:
        // Constructori
        NailService();
        NailService(std::string name, double basePrice);
        NailService(std::string name, double basePrice, bool isGel, int nailCount);
        
        // Setteri
        void SetIsGel(bool isGel);
        void SetNailCount(int count);
        
        // Getteri
        bool IsGel() const;
        int GetNailCount() const;
        
        // Implementari ale metodelor virtuale
        virtual double CalculatePrice() override;
        virtual int EstimateTime() override;
        virtual void DisplayInfo() const override;
    };

    // Clasa pentru servicii spa si tratamente corporale
    class SpaService : public Service {
    private:
        bool m_is_premium;              
        bool m_requires_special_room;   
        
    public:
        // Constructori
        SpaService();
        SpaService(std::string name, double basePrice);
        SpaService(std::string name, double basePrice, bool isPremium, bool requiresSpecialRoom);
        
        // Setteri
        void SetIsPremium(bool isPremium);
        void SetRequiresSpecialRoom(bool requires);
        
        // Getteri
        bool IsPremium() const;
        bool RequiresSpecialRoom() const;
        
        // Implementari ale metodelor virtuale
        virtual double CalculatePrice() override;
        virtual int EstimateTime() override;
        virtual void DisplayInfo() const override;
    };

    // Pachet de servicii (pentru demonstrarea operatorului +)
    class ServicePackage {
    private:
        std::string m_name;                  
        std::vector<Service*> m_services;    
        double m_package_discount;           
        
    public:
        // Constructori si destructor
        ServicePackage();
        ServicePackage(const std::string& name);
        ServicePackage(const std::string& name, double packageDiscount);
        ~ServicePackage();
        
        // Metode pentru gestionarea pachetului
        void AddService(Service* service);
        double CalculateTotalPrice() const;
        int CalculateTotalTime() const;
        void DisplayPackageInfo() const;
        
        // Supraincarcare operator pentru afisare
        friend std::ostream& operator<<(std::ostream& os, const ServicePackage& package);
    };

    // Operator pentru combinarea serviciilor intr-un pachet
    ServicePackage operator+(const Service& lhs, const Service& rhs);
}

#endif // SERVICE_H