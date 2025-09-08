ThisBuild / scalaVersion := "2.13.14"
libraryDependencies ++= Seq(
  "com.typesafe.akka" %% "akka-actor-typed" % "2.9.5",
  "com.typesafe.akka" %% "akka-http" % "10.6.3",
  "org.scalatest" %% "scalatest" % "3.2.19" % Test
)