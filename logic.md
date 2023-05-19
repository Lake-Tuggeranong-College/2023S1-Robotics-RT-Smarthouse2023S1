# Programming Logic

> For each behaviour, create the mermaid flowchart. Start each flowchart with a Heading naming the functionality. Delete this comment prior to submission.

## Logic 1

```mermaid
flowchart TD
    terminalStart([Start])
    %% Comment
    terminalEnd([End])
    thresholdSet(distanceThreshold = 30)
    setPiezoPin(piezoPin = 2)
    currentDistanceReading(distanceRead = response from Sonar)
    activatePiezo(write HIGH to piezoPin)
    deactivatePiezo(write LOW to piezoPin)

    ifDistanceLessThanThreshold{distanceRead < distanceThreshold}

    terminalStart --> thresholdSet
    thresholdSet --> setPiezoPin
    setPiezoPin --> currentDistanceReading
    currentDistanceReading --> ifDistanceLessThanThreshold
    ifDistanceLessThanThreshold --> |True| activatePiezo
    ifDistanceLessThanThreshold --> |False| deactivatePiezo
    deactivatePiezo --> terminalEnd
    activatePiezo --> terminalEnd
```