fn main() {
    let s = erzeuge_string();
    println!("{}", s);
}

fn erzeuge_string() -> String {
    let mut s = String::new();
    s.push_str("Test String");
    return s;
}
