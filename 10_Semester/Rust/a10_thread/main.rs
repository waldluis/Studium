use::std::thread;
use::std::sync::mpsc;


enum Message {
    Increment,
    Decrement(i32),
    Print,
    Shutdown
}



fn main() {

    let (tx, rx) = mpsc::channel();

    let handle = thread::spawn(move || {
        let mut counter = 0;

        loop {
            match rx.recv() {
                Ok(Message::Increment) => {
                    counter += 1;
                },
                Ok(Message::Decrement(value)) => {
                    counter -= value;
                },
                Ok(Message::Print) => {
                    println!("Counter: {}", counter);
                },
                Ok(Message::Shutdown) => {
                    println!("Shutting down");
                    break;
                },
                Err(_) => {
                    break;
                }
            }
        }
    });

    tx.send(Message::Increment).unwrap();
    tx.send(Message::Increment).unwrap();
    tx.send(Message::Print).unwrap();
    tx.send(Message::Decrement(2)).unwrap();
    tx.send(Message::Print).unwrap();
    
    tx.send(Message::Shutdown).unwrap();

    handle.join();

}
