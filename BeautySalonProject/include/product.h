#ifndef PRODUCT_H
#define PRODUCT_H

#include "Interfaces.h"
#include <string>
#include <vector>

namespace Beauty_Salon {
    // Enumeratie pentru categoria produsului
    enum class ProductCategory {
        HAIR_CARE,      
        SKIN_CARE,      
        NAIL_CARE,      
        MAKEUP,         
        ACCESSORIES,    
        OTHER           
    };
    
    // Clasa de bază pentru toate produsele din salon
    class Product : public IDiscountable {
    private:
        int m_id;                     
        std::string m_name;           
        std::string m_brand;          
        double m_price;               
        int m_quantity;               
        ProductCategory m_category;   
        std::string m_description;    
        bool m_is_on_sale;            
        
    protected:
        // Membri statici
        static int m_next_id;        
        static int GenerateID();     
        
    public:
        // Constructori si destructor
        Product();
        Product(const std::string& name, double price);
        Product(const std::string& name, const std::string& brand, double price, ProductCategory category);
        virtual ~Product();
        
        // Getteri
        int GetID() const;
        std::string GetName() const;
        std::string GetBrand() const;
        double GetPrice() const;
        int GetQuantity() const;
        ProductCategory GetCategory() const;
        std::string GetDescription() const;
        bool IsOnSale() const;
        
        // Setteri
        void SetName(const std::string& name);
        void SetBrand(const std::string& brand);
        void SetPrice(double price);
        void SetQuantity(int quantity);
        void SetCategory(ProductCategory category);
        void SetDescription(const std::string& description);
        void SetOnSale(bool onSale);
        
        // Actualizeaza stocul produsului
        bool UpdateStock(int quantity);
        
        // Verifica daca produsul este în stoc
        bool IsInStock() const;
        
        // Implementarea metodei din interfața IDiscountable
        virtual double ApplyDiscount(double amount) override;
        
        // Calculeaza pretul final al produsului (inclusiv reduceri)
        virtual double CalculateFinalPrice() const;
        
        // Afiseaza informatii despre produs
        virtual void DisplayInfo() const;
        
        // Supraincarcarea operatorului de afisare
        friend std::ostream& operator<<(std::ostream& os, const Product& product);
    };

    // Subclasa pentru produse destinate vanzarii catre clienti
    class RetailProduct : public Product {
    private:
        double m_retail_markup;       
        bool m_is_tester_available;   
        
    public:
        // Constructori
        RetailProduct();
        RetailProduct(const std::string& name, double price);
        RetailProduct(const std::string& name, const std::string& brand, double price, 
                     ProductCategory category, double retailMarkup);
        
        // Getteri si setteri
        double GetRetailMarkup() const;
        bool IsTesterAvailable() const;
        
        void SetRetailMarkup(double markup);
        void SetTesterAvailable(bool available);
        
        // Implementari ale metodelor virtuale
        virtual double CalculateFinalPrice() const override;
        virtual void DisplayInfo() const override;
    };

    // Subclasa pentru produse folosite de personalul salonului
    class ProfessionalProduct : public Product {
    private:
        int m_usage_count;                
        std::string m_supplier;           
        bool m_requires_certification;    
        
    public:
        // Constructori
        ProfessionalProduct();
        ProfessionalProduct(const std::string& name, double price);
        ProfessionalProduct(const std::string& name, const std::string& brand, double price, 
                           ProductCategory category, const std::string& supplier);
        
        // Getteri si setteri
        int GetUsageCount() const;
        std::string GetSupplier() const;
        bool RequiresCertification() const;
        
        void SetUsageCount(int count);
        void SetSupplier(const std::string& supplier);
        void SetRequiresCertification(bool requires);
        
        // Incrementeaza contorul de utilizari
        void IncrementUsage();
        
        // Verifica dacă produsul trebuie inlocuit
        bool NeedsReplacement() const;
        
        // Implementari ale metodelor virtuale
        virtual double CalculateFinalPrice() const override;
        virtual void DisplayInfo() const override;
    };

    // Pachet de produse (pentru demonstrarea operatorului +)
    class ProductBundle {
    private:
        std::string m_name;                   
        std::vector<Product*> m_products;     
        double m_bundle_discount;             
        
    public:
        // Constructori si destructor
        ProductBundle();
        ProductBundle(const std::string& name);
        ProductBundle(const std::string& name, double bundleDiscount);
        ~ProductBundle();
        
        // Adauga un produs in pachet
        void AddProduct(Product* product);
        
        // Calculeaza pretul total al pachetului (inclusiv discount)
        double CalculateTotalPrice() const;
        
        // Afiseaza informatii despre pachet
        void DisplayBundleInfo() const;
        
        // Supraincarcarea operatorului de afisare
        friend std::ostream& operator<<(std::ostream& os, const ProductBundle& bundle);
    };

    // Operator pentru combinarea produselor intr-un pachet
    ProductBundle operator+(const Product& lhs, const Product& rhs);
}

#endif // PRODUCT_H