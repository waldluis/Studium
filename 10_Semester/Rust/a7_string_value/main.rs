
fn add_str_values(s1: &str, s2: &str) -> Result<i32, std::num::ParseIntError> {
    let i1 = s1.parse::<i32>()?;
    let i2 = s2.parse::<i32>()?;
    Ok(i1 + i2)
}

fn main() {
    let s1 = "44";
    let s2 = "24";
    match add_str_values(s1, s2) {
        Ok(v) => println!("{} + {} = {}", s1, s2, v),
        Err(e) => println!("Error: {}", e),
    }
}
