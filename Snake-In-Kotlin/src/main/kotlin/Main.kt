import java.awt.EventQueue

fun main(){
    EventQueue.invokeLater {
        val frame = SnakeGame()
        frame.isVisible = true
    }
}