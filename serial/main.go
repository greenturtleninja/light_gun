package main

import (
	"fmt"
	"log"
	"strings"

	"go.bug.st/serial"
)

type IRSensor struct {
	One   Coordinate
	Two   Coordinate
	Three Coordinate
	Four  Coordinate
}

type Coordinate struct {
	XCoord string
	YCoord string
}

func main() {

	// Retrieve the port list
	ports, err := serial.GetPortsList()
	if err != nil {
		log.Fatal(err)
	}
	if len(ports) == 0 {
		log.Fatal("No serial ports found!")
	}

	// Print the list of detected ports
	for _, port := range ports {
		fmt.Printf("Found port: %v\n", port)
	}

	// Open the first serial port detected at 9600bps N81
	mode := &serial.Mode{
		BaudRate: 19200,
		Parity:   serial.NoParity,
		DataBits: 8,
		StopBits: serial.OneStopBit,
	}
	port, err := serial.Open(ports[1], mode)
	if err != nil {
		log.Fatal(err)
	}

	// Send the string "10,20,30\n\r" to the serial port
	//n, err := port.Write([]byte("10,20,30\n\r"))
	//if err != nil {
	//	log.Fatal(err)
	//}
	//fmt.Printf("Sent %v bytes\n", n)
	coordinate := IRSensor{}
	// Read and print the response
	buff := make([]byte, 100)
	for {
		// Reads up to 100 bytes
		n, err := port.Read(buff)
		if err != nil {
			log.Fatal(err)
		}
		if n == 0 {
			fmt.Println("\nEOF")
			break
		}
		if n > 1 {
			coords := getCoordinates(buff, n)
			if len(coords) == 8 {
				coordinate.One = Coordinate{
					XCoord: coords[0],
					YCoord: coords[1],
				}
				coordinate.Two = Coordinate{
					XCoord: coords[2],
					YCoord: coords[3],
				}
				coordinate.Three = Coordinate{
					XCoord: coords[4],
					YCoord: coords[5],
				}
				coordinate.Four = Coordinate{
					XCoord: coords[6],
					YCoord: coords[7],
				}
				fmt.Println(coordinate)
			}

		}

		//fmt.Printf("-read: %d, buff: %s-\n", n, string(buff[:n]))
	}
}

func getCoordinates(buffedStr []byte, buffedLen int) []string {
	//input := string(buffedStr[:buffedLen])
	var output []byte
	for _, b := range buffedStr[:buffedLen] {
		if ('0' <= b && b <= '9') || b == ',' {
			output = append(output, b)
		}
	}
	fmt.Println(output)
	return strings.Split(string(output), ",")
}
