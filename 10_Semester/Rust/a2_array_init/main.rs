fn main() {
    let mut array: [i32;4] = [0;4];
    
    array[0] = 10;
    array[1] = 20;
    array[2] = 30;
    array[3] = 40;

    let sum: i32 = array.iter().sum();
    let average : f64 = sum as f64 / array.len() as f64;
    
    println!("Array: {:?}", array);
    println!("Das ist der Average: {}", average);
}
