import akka.actor.typed.ActorSystem
import akka.http.scaladsl.Http
import akka.http.scaladsl.server.Directives._
import scala.io.StdIn

object AssignmentServer:
  @main def run(): Unit =
    given system: ActorSystem[Nothing] = ActorSystem(akka.actor.typed.scaladsl.Behaviors.empty, "assign")
    val route = path("health"){ get { complete("ok") } } ~ path("replay"){ post { complete("replayed") } }
    val binding = Http().newServerAt("0.0.0.0", 8090).bind(route)
    println("assignment-service on :8090")
    StdIn.readLine()
    binding.flatMap(_.unbind()).onComplete(_ => system.terminate())(using system.executionContext)