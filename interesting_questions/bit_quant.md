## Representing Higher Numbers with Fewer Bits

I was practicing some bit manipulation problems and I came across an interesting question. That question made me think about how we can represent higher numbers with fewer bits if we know that we only need to store even numbers.

I paused for a while and thought about it.

**Questions**

We've all studied in our CS classes how to represent numbers in binary. 

An 8-bit can store 256 possible unsigned values from (0 to 255) in decimal. If we want to store a number higher than that say, 300 we would usually need to use more bits, for example a 9-bit can store 512 possible unsigned values from (0 to 511) in decimal.

But what if our problem or algorithm such that we don't have to store odd numbers? Or if odd numbers are not in the equation at all? Our problem is only concerned with even numbers.

And we've only 8 bits to work with. If we only stored the even numbers from the standard 8-bit range, we would only need to store 128 possible values (0, 2, 4, ..., 254).

This leaves us with 128 `unused` states. 

So can't we use those remaining 128 states to represent higher even numbers beyond 255? (like 300, 400, or up to 510)

I questioned myself, is it possible to store values higher than 255 without actually increasing our `8-bit` size, just by skipping the odd numbers? Are there real world applications or research behind this, or am i just stupidly overthinking it?

Then i began to research (Few Google Searches, and AI Studio) and found our that this actually deduced several core principles of `Information Theory`, `Data Compression`, and `Quantization` in signal processing.

**How is this possible?**

To understand this, we've to separate the `Physical Representation` of the bits from the `Logical Representation` of the values they can represent.

An 8-bit or a byte is just a collection of 8 switches. It has exactly $ 2^8 = 256 $ possible combinations of on/off states. 

- The computer does not naturally know what a decimal number is. It only knows physical  states (on/off) of bits.

- We programmers and hardware designers decide what those 256 states actually represent.

By default, we use standard `unsigned binary encoding` where: 

- State `00000000` means `0`

- State `00000001` means `1`

- State `11111111` means `255`

But there is no reason we have to use that specific mapping. We can define any custom mapping we want.

**The Math**

If we adopt a custom mapping where we only want to represent even numbers, we can define a new mapping formula: 

$$ \text{Value} = \text{Binary State} \times 2 $$

Now, our 8-bit can represent:d

- State `00000000` means `0 * 2 = 0`

- State `00000001` means `1 * 2 = 2`

- State `00000010` means `2 * 2 = 4`

- ...

- State `11111111` means `255 * 2 = 510`

Without adding a single bit, our `8-bit` can now represent even numbers from `0` to `510`, effectively doubling our range of representable values by skipping the odd numbers.

### **How the CPU Processes This**

In binary, multiplying a number by 2 is exactly same as shifting all bits to the left by one position and adding a `0` at the end (Left Shift Operation).

### **Real World Applications**

**Pointer Tagging (JavaScript V8 and JVM)**

In modern 64-bit computers, the operating system allocates memory in blocks of 8 bytes (known as 8-byte alignment). Because memory addresses are always multiples of 8, every single valid memory pointer in binary must end in three zeros: `...000`.

Engineers at Google (working on the Chrome V8 JavaScript engine) and Java developers realized: "Since the last 3 bits of a pointer are always 0, we are wasting 3 bits of memory!". 

They use `Pointer Tagging`. They store useful metadata (like whether a variable is an integer, a string, or an object) directly inside those last 3 bits of the pointer. When the computer actually needs to read the memory address, it clears those 3 bits back to 0. This saves massive amounts of memory across millions of devices.

**Quantization of Models**

Running massive AI models (like ChatGPT or local LLMs) requires gigabytes of memory because the model's "weights" are stored as highly precise 32-bit floating-point numbers.

To make these models run on smaller devices, engineers use `Quantization`. They map those complex 32-bit floating-point numbers into simple 8-bit integers (INT8).

We define a custom scale: 

$$ \text{Quantized Value} = \text{Original Value} \times \text{Scale Factor} $$

Even though the 8-bit byte only has 256 states, they can use those 256 states to represent fractional values like `0.004`, `0.008`, `0.012` all the way up to 1.0. They lose a tiny bit of precision, but the AI model becomes 4x smaller and runs much faster.

### **Implications**

Yes, this is entirely possible and highly practical to implement in C++. 

To implement this, we can wrap a standard 8-bit unsigned integer (`uint8_t`) in a custom C++ class. By using **Bitwise Operators** and **Operator Overloading**, we can make this custom class behave exactly like a native C++ integer, but under the hood, it will store even numbers up to 510 in exactly 1 byte.

Here is the step-by-step implementation and explanation that you can add to your notes.

---

## The C++ Implementation: `EvenByte`

In C++, `uint8_t` is a standard data type (found in the `<cstdint>` header) that takes up exactly **1 byte (8 bits)** of memory. 

To implement your mapping, we perform two simple operations:
1. **To Save (Compress):** Divide the value by 2 using a bitwise **right-shift** (`>> 1`).
2. **To Read (Decompress):** Multiply the value by 2 using a bitwise **left-shift** (`<< 1`).

### The Code

```cpp
#include <iostream>
#include <cstdint>   // For uint8_t (exact 8-bit integer)
#include <stdexcept> // For safety error handling

class EvenByte {
private:
    uint8_t compressed_data; // This physically takes up exactly 1 byte (8 bits)

public:
    // Constructor (starts at 0)
    EvenByte() : compressed_data(0) {}

    // 1. COMPRESS (Write Value)
    // Converts the real even number (0-510) into an 8-bit representation.
    void set(int value) {
        // Safety Checks
        if (value < 0 || value > 510) {
            throw std::out_of_range("Value must be between 0 and 510.");
        }
        if (value % 2 != 0) {
            throw std::invalid_argument("Cannot store odd numbers in EvenByte.");
        }

        // We divide by 2 using a right shift.
        // e.g., 300 (binary 100101100) shifted right becomes 150 (binary 10010110)
        compressed_data = static_cast<uint8_t>(value >> 1);
    }

    // 2. DECOMPRESS (Read Value)
    // Multiplies the stored 8-bit data by 2 to return the original even number.
    int get() const {
        // We multiply by 2 using a left shift.
        // e.g., 150 (binary 10010110) shifted left becomes 300 (binary 100101100)
        return static_cast<int>(compressed_data) << 1;
    }

    // Helper to see exactly what is physically sitting in the RAM
    uint8_t get_raw_byte_value() const {
        return compressed_data;
    }
};

int main() {
    try {
        EvenByte my_num;

        // --- Test 1: Store 300 ---
        my_num.set(300);

        std::cout << "--- Storing 300 ---" << std::endl;
        std::cout << "Actual Value We Want: " << my_num.get() << std::endl;
        std::cout << "Size of our variable in RAM: " << sizeof(my_num) << " byte" << std::endl;
        std::cout << "Physical 8-bit value stored in RAM: " << (int)my_num.get_raw_byte_value() << std::endl;

        // --- Test 2: Store 510 (The absolute limit) ---
        my_num.set(510);

        std::cout << "\n--- Storing 510 ---" << std::endl;
        std::cout << "Actual Value We Want: " << my_num.get() << std::endl;
        std::cout << "Physical 8-bit value stored in RAM: " << (int)my_num.get_raw_byte_value() << std::endl;

        // --- Test 3: Attempting to store an odd number ---
        std::cout << "\n--- Attempting to store 301 ---" << std::endl;
        my_num.set(301); // This will throw an error!

    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}
```

---

## Professional C++ Approach: Operator Overloading

Calling `.set()` and `.get()` manually can be tedious. In real-world C++, we can use **Operator Overloading** to make our custom `EvenByte` class look and feel exactly like a native integer (like `int` or `float`). 

This allows us to write code like `EvenByte x = 300;` and use it directly inside math equations or print statements.

### Advanced Code (Seamless Native Feel)

```cpp
#include <iostream>
#include <cstdint>
#include <stdexcept>

class EvenByte {
private:
    uint8_t compressed_data;

public:
    EvenByte() : compressed_data(0) {}
    EvenByte(int val) { *this = val; } // Constructor that allows "EvenByte x = 300;"

    // Assignment Operator Overload (=)
    // Allows us to write: my_var = 300;
    EvenByte& operator=(int value) {
        if (value < 0 || value > 510 || value % 2 != 0) {
            throw std::invalid_argument("EvenByte can only store even numbers from 0 to 510.");
        }
        compressed_data = static_cast<uint8_t>(value >> 1);
        return *this;
    }

    // Typecast Operator Overload (int)
    // Allows us to write: int x = my_var; or std::cout << my_var;
    operator int() const {
        return static_cast<int>(compressed_data) << 1;
    }
};

int main() {
    try {
        EvenByte a = 300; // Look how natural this is!
        EvenByte b = 100;

        // The compiler automatically decompresses 'a' and 'b' back to 300 and 100
        // to perform the addition, resulting in a standard integer 400.
        int result = a + b; 

        std::cout << "Value of a: " << a << std::endl;
        std::cout << "Value of b: " << b << std::endl;
        std::cout << "Result of a + b: " << result << std::endl;
        std::cout << "Physical memory used by variable 'a': " << sizeof(a) << " byte." << std::endl;

    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    return 0;
}
```

---

## How the Bit Shifts Look In Memory

To visualize what the hardware is doing with the value `300` using the code above:

### Step 1: You pass `300` to the program
The value `300` normally requires **9 bits** to be represented in binary:
$$\text{Value } 300 = \mathbf{1\ 0010\ 1100}_2$$

### Step 2: The right-shift `>> 1` occurs
The compiler pushes all of the bits one slot to the right, discarding the last `0`:
$$\text{Before: } \mathbf{1\ 0010\ 1100} \longrightarrow \text{ After: } \mathbf{1001\ 0110} \text{ (which is 150 in decimal)}$$
Because we only have 8 bits left, it fits perfectly into our 1-byte `uint8_t` variable (`compressed_data`).

### Step 3: You read the value back (`<< 1`)
The compiler takes the 8-bit `150` and shifts it left, padding a `0` on the right:
$$\text{Before: } \mathbf{1001\ 0110} \longrightarrow \text{ After: } \mathbf{1\ 0010\ 1100} \text{ (which is back to 300 in decimal)}$$

Yes, absolutely. This is not just a theoretical exercise—it is one of the most widely used optimization techniques in software engineering. In the industry, this concept is formally known as **Quantization** or **Integer Scaling**.

Whenever engineers need to save network bandwidth, shrink file sizes, or run software on low-power hardware, they use this exact trick of mapping a larger range of values into a smaller set of integer states and then scaling them back.

Here are four major, real-world implementations of this exact technique that you can copy and paste into your notes.

---

# Note Add-on: Real-World Implementations of Integer Scaling

## 1. Multiplayer Game Networking (John Carmack's *Quake*)

In 1996, when John Carmack wrote the code for *Quake* (the grandfather of modern 3D multiplayer shooters), players were using slow 56k dial-up modems. Sending data over the internet was incredibly expensive.

Every player's character has a "looking direction" (yaw, pitch, and roll) which is an angle between $0^\circ$ and $360^\circ$. 
* Normally, a C++ decimal value (`float`) takes up **32 bits (4 bytes)**. Sending three of these (12 bytes) for every single player frame would completely crash a 56k modem.

### The Solution:
The Quake engine compressed the 360-degree angle into a single **8-bit byte** (0 to 255). 

* **On the Server (Compression):** The game divided the player's angle by $\frac{360}{256}$ (approximately $1.4$) and cast it to a single byte.
* **On the Client (Decompression):** When your computer received the packet, it read the byte and ran this exact line of code:
  ```cpp
  float angle = raw_byte * (360.0f / 256.0f);
  ```

By accepting a tiny loss of precision (the player's head could only turn in steps of $1.4^\circ$, which the human eye cannot easily notice), Carmack shrunk the network package size for angles by **75%**.

---

## 2. Hardware Sensors (I2C/SPI Microchips)

If you look at the driver code for physical hardware sensors—like a digital thermometer or an accelerometer used in smartphones—they use this technique constantly.

A temperature sensor might be designed to measure temperatures from $-40^\circ\text{C}$ to $+125^\circ\text{C}$ in steps of $0.5^\circ\text{C}$.

### The Solution:
Instead of trying to process heavy decimal math inside the tiny, cheap microchip on the sensor, the sensor simply outputs a standard 8-bit integer register.

If you read the datasheet for a standard temperature sensor, the C++ driver code to get the temperature looks exactly like this:
```cpp
// The sensor sends an 8-bit byte over the wire (I2C)
uint8_t raw_register = read_sensor_data(); 

// We multiply by our resolution scale factor (0.5 degrees per step)
// and subtract 40 to account for the negative range.
float temperature = (raw_register * 0.5f) - 40.0f;
```
By doing this, the physical microchip only needs to transmit 1 byte of data instead of a complex floating-point package.

---

## 3. Multiplayer Physics Coordinates (Unreal Engine)

In massive multiplayer games like *Fortnite* (built on Unreal Engine), the server has to send the $(X, Y, Z)$ coordinates of every player, bullet, and vehicle to 100 players, many times a second.
n
Coordinates in 3D space are usually 32-bit floats. If a map is very large, a player's coordinate might be something like `14230.54`.

### The Solution:
Unreal Engine uses a feature called **Packed Vectors** or **Quantized replication**. 
If the developers know that players don't need sub-millimeter precision for distant objects, they tell the network serializer to round the float, multiply it by a scale factor, and pack it into a smaller integer.

For example, if we only need precision up to the nearest half-meter ($0.5$), the engine will shift and scale the floats into smaller integer packets before sending them over the internet, saving massive amounts of server bandwidth.

---

## 4. How JPEG and MP3 Files Work

This concept is the absolute core of **lossy compression** (how we make pictures and audio files small enough to stream).

When you save a photo as a `.jpg`, the computer converts the image colors into frequencies. To make the file size small, the computer performs a step called **Quantization**:
1. It divides the pixel data by a "Quantization Table" (which represents scale factors).
2. It rounds the resulting numbers to the nearest whole integer. This turns many small, complex decimal numbers into simple zeros or very small integers.
3. Because there are now many zeros and repeating small numbers, standard ZIP-like compression can shrink the file to a fraction of its original size.
4. When your phone displays the JPEG, it multiplies the numbers back by the same scale factors. 

This is why highly compressed JPEGs look "blocky"—you increased the step size (lost resolution) to make the file size smaller.