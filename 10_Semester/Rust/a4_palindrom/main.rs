
fn is_palindrome(s: &str) -> bool {
    let s = s.to_lowercase();
    let s2 = s.chars().rev().collect::<String>();

    if s == s2 {
        return true;
    } else {
        return false;
    }
    

}

fn is_palindrome2(s: &str) -> bool {
    let mut start = 0;
    let mut end = s.len() - 1;

    while start < end {
        if s[start..=start] != s[end..=end] {
            return false;
        }
        start += 1;
        end -= 1;
    }
    true
}

fn main() {
    let s = "peter";
    let result = is_palindrome(s);
    let result2 = is_palindrome2(s);
    println!("{}", result);
    println!("{}", result2);
}
