use std::fmt::Debug;
use::std::rc::Rc;
use::std::cell::RefCell;


struct Node<T> {
    value: T,
    next: Option<Rc<RefCell<Node<T>>>>,
}


struct LinkedList<T> {
    head: Node<T>
    // head: Option<Rc<RefCell<Node<T>>>>
}

impl<T> LinkedList<T> {
    fn append(&mut self, value: T) {
        match self.head.next {
            Some(ref mut next) => {
                while let nextNode = next.borrow_mut().next{
                
                }
                let new_node = Rc::new(RefCell::new(Node {
                    value: value,
                    next: None,
                }));
                next.borrow_mut().next = Some(new_node);
            },
            None => {
                let new_node = Rc::new(RefCell::new(Node {
                    value: value,
                    next: None,
                }));
                self.head.next = Some(new_node);
            }
        }
    }

    fn pop(&mut self) -> Option<T> {
        match self.head.next {
            Some(ref mut next) => {
                let next_node = next.borrow_mut().next.take();
                let value = next.borrow().value;
                self.head.next = next_node;
                Some(value)
            },
            None => None,
        }
    }

    fn print(&self) {
        println!("{:?} ", self.head.value);
        match self.head.next {
            Some(ref next) => {
                let next = next.borrow();
                println!("{:?} ", next.value);
                while let Some(ref next) = next.next {
                    let next = next.borrow();
                    println!("{:?} ", next.value);
                }
                println!();
            }
            None => println!(),
        }
    }

    fn new(value: T) -> LinkedList<T> {
        LinkedList {
            head: Node {
                value: value,
                next: None,

        }
    }
}

impl<T> Debug for LinkedList<T> {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        write!(f, "LinkedList")
    }
}

impl <T> Debug for Node<T> {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        write!(f, "Node")
    }
}

fn main() {

    let mut list = LinkedList::new(1);

    list.append(2);
    list.append(3);

    list.print();

    list.pop();

    list.print();


    println!("Hello, world!");
}
