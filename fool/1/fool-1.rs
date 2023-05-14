fn main() {
    let mut line = String::new();
    let mut b1 = std::io::stdin().read_line(&mut line).unwrap();
    while b1 != 0 {
        println!("ОK");
        line.clear();
        b1 = std::io::stdin().read_line(&mut line).unwrap();
    }
    // if line != "Connect localhost 80" {
    //     println!("ОK");
    // }
}