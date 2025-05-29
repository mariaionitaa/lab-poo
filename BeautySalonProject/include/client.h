#ifndef CLIENT_H
#define CLIENT_H

#include "Interfaces.h"
#include <string>
#include <vector>
#include <ostream>

namespace Beauty_Salon {
    /**
     * Clasa pentru gestionarea clientilor salonului
     * Implementeaza IDiscountable pentru a oferi reduceri clientilor fideli
     */
    class Client : public IDiscountable {
    private:
        std::string m_name;           
        std::string m_phone;         
        std::string m_email;          
        int m_visits;                 
        bool m_is_vip;                
        double m_loyalty_points;      
        
    public:
        // Membri statici
        static int m_total_clients;   
        static int GetTotalClients(); 
        
        // Constructori si destructor
        Client();
        Client(const std::string& name);
        Client(const std::string& name, const std::string& phone);
        Client(const std::string& name, const std::string& phone, const std::string& email);
        ~Client();
        
        // Getteri
        std::string GetName() const;
        std::string GetPhone() const;
        std::string GetEmail() const;
        int GetVisits() const;
        bool IsVIP() const;
        double GetLoyaltyPoints() const;
        
        // Setteri
        void SetPhone(const std::string& phone);
        void SetEmail(const std::string& email);
        void SetVIP(bool isVip);
        
        // Adauga o vizita si actualizeaza statusul si punctele de loialitate
        void AddVisit();
        
        // Adauga puncte de loialitate
        void AddLoyaltyPoints(double points);
        
        // Foloseste puncte de loialitate pentru a obtine un discount
        bool UseLoyaltyPoints(double points);
        
        // Implementarea metodei din interfata IDiscountable
        virtual double ApplyDiscount(double amount) override;
        
        // Afiseaza informatii despre client
        void DisplayInfo() const;
        
        // Supraincarcarea operatorului pentru afisare
        friend std::ostream& operator<<(std::ostream& os, const Client& client);
    };
}

#endif // CLIENT_H