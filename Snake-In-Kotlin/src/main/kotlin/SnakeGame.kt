import javax.swing.JFrame

class SnakeGame : JFrame() {
    init{
        add(GamePanel())
        pack()
        setLocationRelativeTo(null)
        defaultCloseOperation = JFrame.EXIT_ON_CLOSE
    }
}