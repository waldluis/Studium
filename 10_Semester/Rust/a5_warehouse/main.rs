
struct Product {
    name: String,
    amount: u32,
    price: f64
}

impl Product {
    fn new_product(name: String, amount: u32, price: f64) -> Product {
        Product {
            name,
            amount,
            price
        }
    }

    fn value(&self) -> Option<f64> {
        match self.amount {
            0 => None,
            _ => Some(self.amount as f64 * self.price)
        }
    }
}

fn main() {
    let product = Product::new_product("Apple".to_string(), 10, 1.5);
    println!("Product: {}, Amount: {}, Price: {}", product.name, product.amount, product.price);
    let value = product.value();
    println!("Value: {:?}", value);

    let product2 = Product::new_product("Banana".to_string(), 20, 2.5);
    println!("Product: {}, Amount: {}, Price: {}", product2.name, product2.amount, product2.price);
    let value = product2.value();
    println!("Value: {:?}", value);

    let product3 = Product::new_product("Orange".to_string(), 30, 3.5);
    println!("Product: {}, Amount: {}, Price: {}", product3.name, product3.amount, product3.price);
    let value = product3.value();
    println!("Value: {:?}", value);

    let product4 = Product::new_product("Pineapple".to_string(), 0, 4.5);
    println!("Product: {}, Amount: {}, Price: {}", product4.name, product4.amount, product4.price);
    let value = product4.value();
    println!("Value: {:?}", value);
}
