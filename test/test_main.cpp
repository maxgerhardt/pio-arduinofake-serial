#include <ArduinoFake.h>
#include <unity.h>

using namespace fakeit;

void test_setup(void)
{
    // Setup expectation and return values
    When(OverloadedMethod(ArduinoFake(Serial), begin, void(unsigned long))).Return();
    When(Method(ArduinoFake(), pinMode)).Return();

    // Run method under test
    setup();

    // Verify expectations with actually used paramters
    Verify(OverloadedMethod(ArduinoFake(Serial), begin, void(unsigned long)).Using((unsigned long) 9600)).Once();
    Verify(Method(ArduinoFake(), pinMode).Using(LED_BUILTIN, OUTPUT)).Once();
}

void test_loop_turns_on_led(void)
{
    String fakedInput = "turnon";
    When(Method(ArduinoFake(Serial), available)).Return(fakedInput.length());
    When(Method(ArduinoFake(Serial), readStringUntil)).Return(fakedInput);
    When(Method(ArduinoFake(), digitalWrite)).AlwaysReturn();
    
    loop();

    Verify(Method(ArduinoFake(Serial), available)).Once();
    Verify(Method(ArduinoFake(Serial), readStringUntil).Using('\n')).Once();
    Verify(Method(ArduinoFake(), digitalWrite).Using(LED_BUILTIN, HIGH)).Once();
}

void test_loop_turns_off_led(void)
{
    String fakedInput = "turnoff";
    When(Method(ArduinoFake(Serial), available)).Return(fakedInput.length());
    When(Method(ArduinoFake(Serial), readStringUntil)).Return(fakedInput);
    When(Method(ArduinoFake(), digitalWrite)).AlwaysReturn();
    
    loop();

    Verify(Method(ArduinoFake(Serial), available)).Once();
    Verify(Method(ArduinoFake(Serial), readStringUntil).Using('\n')).Once();
    Verify(Method(ArduinoFake(), digitalWrite).Using(LED_BUILTIN, LOW)).Once();
}

void setUp(void)
{
    ArduinoFakeReset();
}

void tearDown(void) {}

int main(int argc, char **argv)
{
    UNITY_BEGIN();

    RUN_TEST(test_setup);
    RUN_TEST(test_loop_turns_on_led);
    RUN_TEST(test_loop_turns_off_led);

    UNITY_END();

    return 0;
}