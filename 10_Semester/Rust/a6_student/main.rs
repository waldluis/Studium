pub struct Studierender {
    name: String,
    matrikel: u32,
    age: u32,
}

impl Studierender {
    fn to_str(&self) -> String {
        format!("Name: {}, Matrikel: {}, Alter: {}", self.name, self.matrikel, self.age)
    }
}

pub enum StudElement {
    Student(Studierender),
    Studentin(Studierender),
}

fn aeltester_student(v: &Vec<StudElement>) -> Option<&Studierender> {
    let mut max_age = 0;
    let mut oldest_student = None;

    for s in v {
        if let StudElement::Student(m) = s {
            if m.age > max_age {
                max_age = s.age;
                oldest_student = Some(s);
            }
        }
    }
    oldest_student
}

fn main() {
    let v = vec![
        StudElement::Student(Studierender {name: String::from("Meier"), matrikel: 1, age: 20}),
        StudElement::Studentin(Studierender {name: String::from("Müller"), matrikel: 2, age: 21}),
        StudElement::Student(Studierender {name: String::from("Schmidt"), matrikel: 3, age: 19}),
        StudElement::Studentin(Studierender {name: String::from("Weber"), matrikel: 4, age: 20}),
        StudElement::Student(Studierender {name: String::from("Schulz"), matrikel: 5, age: 22})];

    if let Some(s) = aeltester_student(&v) {
        println!("Der älteste Student heißt {}", s.name);
    }

    for s in &v {
        match s {
            StudElement::Student(s) => println!("{}", s.to_str()),
            StudElement::Studentin(s) => println!("{}", s.to_str()),
        }
    }
}
