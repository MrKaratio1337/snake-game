import java.awt.Color
import java.awt.Dimension
import java.awt.Font
import java.awt.Graphics
import java.awt.event.ActionEvent
import java.awt.event.ActionListener
import java.awt.event.KeyAdapter
import java.awt.event.KeyEvent
import javax.swing.JPanel
import javax.swing.Timer

class GamePanel : JPanel(), ActionListener {
    private val screenWidth = 600
    private val screenHeight = 600
    private val unitSize = 25
    private val gameUnits = (screenWidth * screenHeight) / unitSize
    private val delay = 100

    private val x = IntArray(gameUnits)
    private val y = IntArray(gameUnits)
    private var bodyParts = 6
    private var applesEaten = 0
    private var appleX = 0
    private var appleY = 0
    private var direction = 'R'
    private var running = false
    private var timer: Timer? = null

    init{
        preferredSize = Dimension(screenWidth, screenHeight)
        background = Color.black
        isFocusable = true
        addKeyListener(MyKeyAdapter())
        startGame()
    }

    private fun startGame(){
        newApple()
        running = true
        timer = Timer(delay, this)
        timer!!.start()
    }

    private fun newApple(){
        appleX = (Math.random() * (screenWidth / unitSize)).toInt() * unitSize
        appleY = (Math.random() * (screenHeight / unitSize)).toInt() * unitSize
    }

    override fun paintComponent(g: Graphics) {
        super.paintComponent(g)
        draw(g)
    }

    private fun draw(g: Graphics){
        if(running){
            g.color = Color.red
            g.fillRect(appleX, appleY, unitSize, unitSize)

            for(i in 0 until bodyParts){
                g.color = if (i == 0) Color.green else Color.green.darker()
                g.fillRect(x[i], y[i], unitSize, unitSize)
            }

            g.color = Color.white
            g.font = Font("Arial", Font.BOLD, 40)
            val metrics = getFontMetrics(g.font)
            g.drawString("Score: $applesEaten", (screenWidth - metrics.stringWidth("Score: $applesEaten")) / 2, g.font.size)
        } else{
            gameOver(g)
        }
    }

    private fun move(){
        for(i in bodyParts downTo 1){
            x[i] = x[i - 1]
            y[i] = y[i - 1]
        }

        when(direction){
            'U' -> y[0] -= unitSize
            'D' -> y[0] += unitSize
            'L' -> x[0] -= unitSize
            'R' -> x[0] += unitSize
        }
    }

    private fun checkApple(){
        if(x[0] == appleX && y[0] == appleY){
            bodyParts++
            applesEaten++
            newApple()
        }
    }

    private fun checkCollisions(){
        for(i in bodyParts downTo 1){
            if(x[0] == x[i] && y[0] == y[i]){
                running = false
            }
        }

        if(x[0] < 0 || x[0] > screenWidth || y[0] < 0 || y[0] > screenHeight){
            running = false
        }

        if(!running)
            timer!!.stop()
    }

    private fun gameOver(g: Graphics){
        g.color = Color.red
        g.font = Font("Arial", Font.BOLD, 75)
        val metrics = getFontMetrics(g.font)
        g.drawString("Game Over", (screenWidth - metrics.stringWidth("Game Over")) / 2, screenHeight / 2)

        g.font = Font("Arial", Font.BOLD, 40)
        g.drawString("Score: $applesEaten", (screenWidth - metrics.stringWidth("Score: $applesEaten")) / 2, screenHeight / 2 * 50)
    }

    override fun actionPerformed(e: ActionEvent) {
        if(running){
            move()
            checkApple()
            checkCollisions()
        }

        repaint()
    }

    private inner class MyKeyAdapter : KeyAdapter(){
        override fun keyPressed(e: KeyEvent) {
            when(e.keyCode){
                KeyEvent.VK_LEFT -> if(direction != 'R') direction = 'L'
                KeyEvent.VK_RIGHT -> if(direction != 'L') direction = 'R'
                KeyEvent.VK_UP -> if(direction != 'D') direction = 'U'
                KeyEvent.VK_DOWN -> if(direction != 'U') direction = 'D'
            }
        }
    }
}