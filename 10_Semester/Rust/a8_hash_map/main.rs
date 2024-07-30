use std::collections::HashMap;

fn main() {
    let mut dict = HashMap::new();
    let stdin = std::io::stdin();

    loop {
        println!("Enter a english word and the german translation (e.g. 'apple::Apfel'):");
        let mut input = String::new();
        let result = stdin.read_line(&mut input);

        match result {
            Ok(_) => {
                if input.contains("::") {
                    let parts: Vec<&str> = input.trim().split("::").collect();
                    dict.insert(parts[0].to_string(), parts[1].to_string());
                } else {
                    let output = dict.get(&input.trim().to_string());
                    match output {
                        Some(value) => println!("The german translation is: {}", value),
                        None => println!("The word is not in the dictionary"),
                    }
                }
            }
            Err(error) => {
                println!("Error: {}", error);
                break;
            }
        }
    }
}
